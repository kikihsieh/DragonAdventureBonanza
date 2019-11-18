#include <ecs/entities/cloud.hpp>
#include <sstream>
#include <ecs/systems/flying_physics_system.hpp>
#include <ecs/entities/final_boss.hpp>
#include "night_sky.hpp"

NightSky::NightSky(bool unlocked) :
        Level(unlocked) {
}

bool NightSky::init() {
    bool init = Level::init();

    m_rng = std::default_random_engine(std::random_device()());
    m_screen = {1200, 800};

    m_physics_system = new FlyingPhysicsSystem();
    m_physics_system->init(&m_entities, m_screen);

    for (auto &iter : m_texture_map) {
        auto texture = std::make_shared<Texture>();
        if (!texture->is_valid()) {
            if (!texture->load_from_file(iter.second)) {
                fprintf(stderr, "Failed to load tile texture!");
                return false;
            }
        }
        m_texture_mapping.insert(TextureMapping::value_type(iter.first, texture));
    }

    m_spawn_cloud_frequency = 5500;
    m_spawn_cloud_timer = m_spawn_cloud_frequency;

    for (float x = 0; x <= 1300; x += 150) {
        float y = 20 + dist(m_rng) * (m_screen.y - 20);
        Cloud c(m_texture_mapping.at(round(1 + dist(m_rng))), {x, y});
        if (init_entity(c)) {
            auto it = m_entities.begin();
            std::advance(it, (int)m_entities.size() / 2);
            m_entities.insert(it, c);
        }
    }

    m_player->physics->gravity = 0;
    m_player->physics->velocity = {0, 0};
    m_player->physics->acceleration = {0, 0};
    m_player->position = {100, 400};

    FinalBoss b(m_texture_mapping.at(3), {m_screen.x - 100, m_screen.y / 2});
    if (!init_entity(b))
        return false;
    m_entities.push_back(b);

    return init;
}


void NightSky::update(float elapsed_ms, vec2 screen_size) {
    m_player->input->space = true;

    Level::update(elapsed_ms, screen_size);

    m_spawn_cloud_timer += elapsed_ms;
    if (m_spawn_cloud_timer >= m_spawn_cloud_frequency) {
        spawn_cloud();
        m_spawn_cloud_timer = 0;
    }
}


void NightSky::spawn_cloud() {
    float y = 20 + dist(m_rng) * (m_screen.y - 20);
    Cloud c(m_texture_mapping.at(round(1 + dist(m_rng))), {m_screen.x + 50, y});
    if (init_entity(c)) {
        auto it = m_entities.begin();
        std::advance(it, (int)m_entities.size() / 2);
        m_entities.insert(it, c);
    }
}


bool NightSky::init_entity(Entity& entity) {

    if (entity.drawable == nullptr) {
        return false;
    }

    Drawable * drawable = entity.drawable;
    if (!entity.drawable->texture->is_valid()) {
        if (!entity.drawable->texture->load_from_file(entity.drawable->texture_path)){
            fprintf(stderr, "Failed to load %s texture!", entity.drawable->texture_path);
            return false;
        }
    }
    entity.texture_size = {drawable->texture->width * 1.f, drawable->texture->height * 1.f};
    // The position corresponds to the center of the texture
    float wr = drawable->texture->width * 0.5f;
    float hr = drawable->texture->height * 0.5f;

    drawable->vertices[0].position = { -wr, +hr, -0.02f };
    drawable->vertices[0].texcoord = { 0.f, 1.f };
    drawable->vertices[1].position = { +wr, +hr, -0.02f };
    drawable->vertices[1].texcoord = { 1.f, 1.f };
    drawable->vertices[2].position = { +wr, -hr, -0.02f };
    drawable->vertices[2].texcoord = { 1.f, 0.f };
    drawable->vertices[3].position = { -wr, -hr, -0.02f };
    drawable->vertices[3].texcoord = { 0.f, 0.f };

    // Counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = { 0, 3, 1, 1, 3, 2 };

    // Clearing errors
    gl_flush_errors();

    // Vertex Buffer creation
    glGenBuffers(1, &drawable->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, drawable->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, drawable->vertices, GL_STATIC_DRAW);

    // Index Buffer creation
    glGenBuffers(1, &drawable->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);

    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &drawable->vao);
    if (gl_has_errors())
        return false;

    // Loading shaders: check if it's already in memory
    if (m_effects.find(drawable->vs_shader) == m_effects.end()){
        if (!load_from_file(drawable->effect, drawable->vs_shader, drawable->fs_shader))
            return false;
        m_effects[drawable->vs_shader] = drawable->effect;
    }else{
        drawable->effect = m_effects[drawable->vs_shader];
    };
    return true;
}

namespace
{
    bool gl_compile_shader(GLuint shader)
    {
        glCompileShader(shader);
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLint log_len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
            std::vector<char> log(log_len);
            glGetShaderInfoLog(shader, log_len, &log_len, log.data());
            glDeleteShader(shader);

            fprintf(stderr, "GLSL: %s", log.data());
            return false;
        }

        return true;
    }
}

bool NightSky::load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path)
{
    gl_flush_errors();

    // Opening files
    std::ifstream vs_is(vs_path);
    std::ifstream fs_is(fs_path);

    if (!vs_is.good() || !fs_is.good())
    {
        fprintf(stderr, "Failed to load shader files %s, %s", vs_path, fs_path);
        return false;
    }

    // Reading sources
    std::stringstream vs_ss, fs_ss;
    vs_ss << vs_is.rdbuf();
    fs_ss << fs_is.rdbuf();
    std::string vs_str = vs_ss.str();
    std::string fs_str = fs_ss.str();
    const char* vs_src = vs_str.c_str();
    const char* fs_src = fs_str.c_str();
    GLsizei vs_len = (GLsizei)vs_str.size();
    GLsizei fs_len = (GLsizei)fs_str.size();

    effect.vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(effect.vertex, 1, &vs_src, &vs_len);
    effect.fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(effect.fragment, 1, &fs_src, &fs_len);

    // Compiling
    // Shaders already delete if compilation fails
    if (!gl_compile_shader(effect.vertex))
        return false;

    if (!gl_compile_shader(effect.fragment))
    {
        glDeleteShader(effect.vertex);
        return false;
    }

    // Linking
    effect.program = glCreateProgram();
    glAttachShader(effect.program, effect.vertex);
    glAttachShader(effect.program, effect.fragment);
    glLinkProgram(effect.program);
    {
        GLint is_linked = 0;
        glGetProgramiv(effect.program, GL_LINK_STATUS, &is_linked);
        if (is_linked == GL_FALSE)
        {
            GLint log_len;
            glGetProgramiv(effect.program, GL_INFO_LOG_LENGTH, &log_len);
            std::vector<char> log(log_len);
            glGetProgramInfoLog(effect.program, log_len, &log_len, log.data());

            release(effect);
            fprintf(stderr, "Link error: %s", log.data());
            return false;
        }
    }

    if (gl_has_errors())
    {
        release(effect);
        fprintf(stderr, "OpenGL errors occured while compiling Effect");
        return false;
    }

    return true;
}

void NightSky::release(Drawable::Effect &effect)
{
    glDeleteProgram(effect.program);
    glDeleteShader(effect.vertex);
    glDeleteShader(effect.fragment);
}

void NightSky::destroy_entity(Entity& entity) {
    glDeleteBuffers(1, &entity.drawable->vbo);
    glDeleteShader(entity.drawable->effect.vertex);
    glDeleteShader(entity.drawable->effect.fragment);
    glDeleteShader(entity.drawable->effect.program);
}
