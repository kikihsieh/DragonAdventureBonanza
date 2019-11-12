#include "shooting_system.hpp"
#include "render_system.hpp"

#include <cmath>
#include <utility>
#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <sstream>

const size_t PLAYER_PROJ_DELAY_MS = 400; //around 5 clicks
const size_t ENEMY_PROJ_DELAY_MS = 6000;

bool ShootingSystem::init(std::list<Entity> *entities, TextureMapping mapping, Entity *player, vec2 bounds) {
    m_entities = entities;
    m_texture_mapping = mapping;
    m_player = player;
    m_next_player_projectile = 0.f;
    m_next_enemy_projectile = 0.f;
    m_rng = std::default_random_engine(std::random_device()());
    m_bounds = bounds;
    return true;
}

// texture Mapping KEY:
// -7 is player projectile: fireball
// -6 is enemy projectile: depends on scene

void ShootingSystem::update(float ms) {
    for (auto &entity : *m_entities){
        if (!entity.shooting) {
            continue;
        }
        if (entity.input && entity.input->space) {
            vec2 pos = {entity.position.x, entity.position.y + 10.f};
            vec2 shoot_direction = { 1.f, 0.f };
            vec2 texture_scale = { 1.0f, 1.0f };
            
            if (!entity.is_facing_forward) {
                shoot_direction = { -1.f, 0.f };
                texture_scale = { -1.0f, 1.0f };
            }
            
            m_next_player_projectile -= ms;
            if (m_next_player_projectile < 0.f) {
                Projectile p(m_texture_mapping.at(-7), pos, shoot_direction, texture_scale, false);
                if (initEntity(p)) {
                    m_entities->emplace_back(p);
                }
                m_next_player_projectile = ((PLAYER_PROJ_DELAY_MS)/2) + m_dist(m_rng) * ((PLAYER_PROJ_DELAY_MS)/2);
            }
        }
        else if (entity.enemyai) {
            vec2 pos = entity.position;
            vec2 shoot_direction = normalize({-1.f*(entity.position.x - m_player->position.x), -1.f*(entity.position.y - m_player->position.y)});
            vec2 texture_scale = { 1.0f, 1.0f };
            
            m_next_enemy_projectile -= ms;
            float hor_dist = abs(entity.position.x - m_player->position.x);
            float vert_dist = abs(entity.position.y - m_player->position.y);
            if (hor_dist < 300.f && vert_dist < 300.f && m_next_enemy_projectile < 0.f) {
                Projectile p(m_texture_mapping.at(-6), pos, shoot_direction, texture_scale, true);
                if (initEntity(p)) {
                    m_entities->emplace_back(p);
                }
                m_next_enemy_projectile = ((ENEMY_PROJ_DELAY_MS) / 2) + m_dist(m_rng) * ((ENEMY_PROJ_DELAY_MS)/2);
            }
        }
    }
}

//RENDERING PROJECTILE ENTITIES
bool ShootingSystem::initEntity(Entity& entity) {
    
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

bool ShootingSystem::load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path)
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

void ShootingSystem::release(Drawable::Effect &effect)
{
    glDeleteProgram(effect.program);
    glDeleteShader(effect.vertex);
    glDeleteShader(effect.fragment);
}

void ShootingSystem::destroyEntity(Entity& entity) {
    glDeleteBuffers(1, &entity.drawable->vbo);
    glDeleteShader(entity.drawable->effect.vertex);
    glDeleteShader(entity.drawable->effect.fragment);
    glDeleteShader(entity.drawable->effect.program);
}
