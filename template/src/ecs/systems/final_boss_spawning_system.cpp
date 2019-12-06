#include "final_boss_spawning_system.hpp"
#include <ecs/entities/final_boss.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <ecs/entities/cloud.hpp>
#include <ecs/entities/projectile.hpp>
#include <cmath>
#include <ecs/entities/sibling.hpp>

#define PI 3.14159265359

FinalBossSpawningSystem::~FinalBossSpawningSystem() {
    for (auto &shader : m_effects) {
        glDeleteShader(shader.second.vertex);
        glDeleteShader(shader.second.fragment);
        glDeleteProgram(shader.second.program);
    }
}

bool FinalBossSpawningSystem::init(std::list<Entity> *entities, vec2 screen_size) {
    m_entities = entities;
    m_screen_bounds = screen_size;
    m_rng = std::default_random_engine(std::random_device()());

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

    return true;
}


bool FinalBossSpawningSystem::spawn_final_boss() {
    FinalBoss b(m_texture_mapping.at(3), {m_screen_bounds.x - 150, m_screen_bounds.y / 2});
    if (!init_entity(b))
        return false;
    b.texture_size = {b.texture_size.x * 0.7f, b.texture_size.y * 0.7f};
    m_entities->push_back(b);
    return true;
}

void FinalBossSpawningSystem::spawn_cloud(float x_offset) {
    float y = 20 + dist(m_rng) * (m_screen_bounds.y - 20);
    float x = m_screen_bounds.x + 50 - x_offset;

    Cloud c(m_texture_mapping.at(round(1 + dist(m_rng))), {x, y});
    if (init_entity(c)) {
        auto it = m_entities->begin();
        std::advance(it, 1);
        m_entities->insert(it, c);
    }
}

void FinalBossSpawningSystem::spawn_bomb(vec2 position) {
    Projectile b(m_texture_mapping.at(4), position, {-1.5, 0}, {0.1f, 0.1f}, true);
    b.physics->gravity = 0;
    b.physics->acceleration.y = 0;
    b.is_bomb = true;
    b.is_boss_proj = true;
    if (init_entity(b))
        m_entities->push_back(b);
}

void FinalBossSpawningSystem::explode_bomb(vec2 position) {

    Projectile p1(m_texture_mapping.at(4), position, {1, 0}, {0.05f, 0.05f}, true);
    p1.physics->gravity = 0;
    p1.physics->acceleration.y = 0;
    p1.is_boss_proj = true;
    p1.clipped = false;
    p1.radians = PI;
    if (init_entity(p1))
        m_entities->push_back(p1);

    Projectile p2(m_texture_mapping.at(4), position,
                  normalize({(float)sqrt(3), 1}), {0.05f, 0.05f}, true);
    p2.physics->gravity = 0;
    p2.physics->acceleration.y = 0;
    p2.is_boss_proj = true;
    p2.clipped = false;
    p2.radians = PI + 0.65138788668;
    if (init_entity(p2))
        m_entities->push_back(p2);

    Projectile p3(m_texture_mapping.at(4), position,
                  normalize({(float)sqrt(3), -1}), {0.05f, 0.05f}, true);
    p3.physics->gravity = 0;
    p3.physics->acceleration.y = 0;
    p3.is_boss_proj = true;
    p3.clipped = false;
    p3.radians = PI - 0.65138788668;
    if (init_entity(p3))
        m_entities->push_back(p3);

    Projectile p4(m_texture_mapping.at(4), position,
                  normalize({1, (float)sqrt(3)}), {0.05f, 0.05f}, true);
    p4.physics->gravity = 0;
    p4.physics->acceleration.y = 0;
    p4.is_boss_proj = true;
    p4.clipped = false;
    p4.radians = PI + 0.91940844011;
    if (init_entity(p4))
        m_entities->push_back(p4);

    Projectile p5(m_texture_mapping.at(4), position,
                  normalize({1, -(float)sqrt(3)}), {0.05f, 0.05f}, true);
    p5.physics->gravity = 0;
    p5.physics->acceleration.y = 0;
    p5.is_boss_proj = true;
    p5.clipped = false;
    p5.radians = PI - 0.91940844011;
    if (init_entity(p5))
        m_entities->push_back(p5);

    Projectile p6(m_texture_mapping.at(4), position, {0, 1}, {0.05f, 0.05f}, true);
    p6.physics->gravity = 0;
    p6.physics->acceleration.y = 0;
    p6.is_boss_proj = true;
    p6.clipped = false;
    p6.radians = PI / -2;
    if (init_entity(p6))
        m_entities->push_back(p6);

    Projectile p7(m_texture_mapping.at(4), position, {0, -1}, {0.05f, 0.05f}, true);
    p7.physics->gravity = 0;
    p7.physics->acceleration.y = 0;
    p7.is_boss_proj = true;
    p7.clipped = false;
    p7.radians = PI / 2;
    if (init_entity(p7))
        m_entities->push_back(p7);
}

void FinalBossSpawningSystem::spawn_minion(vec2 position, vec2 dir, int health) {
    Sibling s(m_texture_mapping.at(5), position, dir, {0.25, 0.25}, health);
    if (init_entity(s))
        m_entities->push_back(s);
}

void FinalBossSpawningSystem::spawn_wave(vec2 position) {

    float y;
    float x = 1;
    float safe_angle = -0.261799 + dist(m_rng) * 2 * 0.261799;

    float angle_increment = 0.0872665;
    for (float i = -PI/2 + angle_increment / 100; i <= PI/2; i += angle_increment) {

        if (abs(i - safe_angle) <= angle_increment)
            continue;

        y = tan(i) * x;

        Projectile p(m_texture_mapping.at(4), position,
                     normalize({-x, y}), {0.05f, 0.05f}, true);
        p.physics->gravity = 0;
        p.physics->acceleration.y = 0;
        p.is_boss_proj = true;
        p.radians = -i;
        if (init_entity(p))
            m_entities->push_back(p);
    }
}


void FinalBossSpawningSystem::spawn_wall(vec2 position) {

    float x = 1;
    float safe_y = 300 + dist(m_rng) * (m_screen_bounds.y - 2 * 300);

    float increment = 50;

    for (float y = 0; y <= m_screen_bounds.y; y += increment) {
        if (abs(y - safe_y) < increment * 1.5) {
            if (abs(y - safe_y) < increment / 2) {
                spawn_minion({position.x, safe_y}, {-1.75, 0}, 2);
            }
            continue;
        }

        Projectile p(m_texture_mapping.at(4), {position.x, y},
                     normalize({-x, 0}), {0.05f, 0.05f}, true);
        p.physics->gravity = 0;
        p.physics->acceleration.y = 0;
        p.is_boss_proj = true;
        if (init_entity(p))
            m_entities->push_back(p);
    }
}

void FinalBossSpawningSystem::spawn_radial(vec2 position, float offset) {

    float y;
    float x = 1;

    float angle_increment = 0.26;
    for (float i = -PI/2 - offset; i < PI/2+ offset; i += angle_increment) {

        y = tan(i) * x;

        Projectile p(m_texture_mapping.at(4), position,
                     normalize({-x, y}), {0.05f, 0.05f}, true);
        p.physics->gravity = 0;
        p.physics->acceleration.y = 0;
        p.is_boss_proj = true;
        p.radians = -i;
        if (i < -PI/2 || i > PI/2)
            p.radians = i;
        if (init_entity(p))
            m_entities->push_back(p);
    }
}


float FinalBossSpawningSystem::spawn_maze(vec2 position, float last_safe_y, int count) {

    float x = 1;
    float increment = 100;

    float safe_y = last_safe_y;

    if (count == 0) {
        float rng = dist(m_rng);
        if (rng > (((m_screen_bounds.y / 2) - last_safe_y) / (2 * (m_screen_bounds.y / 2 - increment))) + 0.5)
            safe_y -= increment;
        else
            safe_y += increment;
    }

    if (safe_y < increment)
        safe_y = increment;
    if (safe_y > m_screen_bounds.y - increment)
        safe_y = m_screen_bounds.y - increment;

    for (float y = 0; y <= m_screen_bounds.y; y += increment) {
        if (abs(y - safe_y) < increment || abs(y - last_safe_y) < increment) {
            continue;
        }

        Projectile p(m_texture_mapping.at(4), {position.x, y},
                     {-x * 0.95f, 0}, {0.05f, 0.05f}, true);
        p.physics->gravity = 0;
        p.physics->acceleration.y = 0;
        p.is_boss_proj = true;
        if (init_entity(p))
            m_entities->push_back(p);
    }

    return safe_y;
}

bool FinalBossSpawningSystem::init_entity(Entity& entity) {

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

bool FinalBossSpawningSystem::load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path) {
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

void FinalBossSpawningSystem::release(Drawable::Effect &effect) {
    glDeleteProgram(effect.program);
    glDeleteShader(effect.vertex);
    glDeleteShader(effect.fragment);
}

void FinalBossSpawningSystem::destroy_entity(Entity& entity) {
    glDeleteBuffers(1, &entity.drawable->vbo);
    glDeleteShader(entity.drawable->effect.vertex);
    glDeleteShader(entity.drawable->effect.fragment);
    glDeleteShader(entity.drawable->effect.program);
}