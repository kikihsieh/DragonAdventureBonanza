#include "render_system.hpp"
#include <vector>
#include <list>
#include <sstream>
#include <cmath>
#include <ecs/entities/tile.hpp>

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {
    for (auto &shader : m_effects) {
        glDeleteShader(shader.second.vertex);
        glDeleteShader(shader.second.fragment);
        glDeleteShader(shader.second.program);
    }
    for (Entity &entity: *m_entities) {
        if (!entity.drawable) {
            continue;
        }
        glDeleteBuffers(1, &entity.drawable->vbo);
        glDeleteBuffers(1, &entity.drawable->ibo);
        glDeleteVertexArrays(1, &entity.drawable->vao);
    }
    for (auto &tile : *m_tiles) {
        if (!tile.second->drawable) {
            continue;
        }
        glDeleteBuffers(1, &tile.second->drawable->vbo);
        glDeleteBuffers(1, &tile.second->drawable->ibo);
        glDeleteVertexArrays(1, &tile.second->drawable->vao);
    }
}

bool RenderSystem::init(std::list<Entity> *entities, std::map<int, Tile*>* tiles) {
    m_effects = {};
    m_entities = entities;

    for (auto &entity : *entities) {
        if (entity.drawable == nullptr) {
            continue;
        }
        initEntity(entity);
    }
    m_tiles = tiles;
    for (auto &tile : *m_tiles) {
        if (tile.second->drawable == nullptr) {
            continue;
        }
        initEntity(*tile.second);
    }
    return true;
}

bool RenderSystem::initEntity(Entity &entity) {
    Drawable *drawable = entity.drawable;
    if (!entity.drawable->texture->is_valid()) {
        if (!entity.drawable->texture->load_from_file(entity.drawable->texture_path)) {
            fprintf(stderr, "Failed to load %s texture!", entity.drawable->texture_path);
            return false;
        }
    }
    entity.texture_size = {drawable->texture->width * 1.f, drawable->texture->height * 1.f};

    if (entity.animatable) {
        entity.texture_size = mul(entity.texture_size, {1.f/entity.animatable->num_columns, 1.f/entity.animatable->num_rows });
    }

    // The position corresponds to the center of the texture
    float wr = entity.texture_size.x * 0.5f;
    float hr = entity.texture_size.y * 0.5f;

    drawable->vertices[0].position = {-wr, +hr, -0.02f};
    drawable->vertices[0].texcoord = {0.f, 1.f};
    drawable->vertices[1].position = {+wr, +hr, -0.02f};
    drawable->vertices[1].texcoord = {1.f, 1.f};
    drawable->vertices[2].position = {+wr, -hr, -0.02f};
    drawable->vertices[2].texcoord = {1.f, 0.f};
    drawable->vertices[3].position = {-wr, -hr, -0.02f};
    drawable->vertices[3].texcoord = {0.f, 0.f};

    // Counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = {0, 3, 1, 1, 3, 2};

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
    if (m_effects.find(drawable->vs_shader) == m_effects.end()) {
        if (!load_from_file(drawable->effect, drawable->vs_shader, drawable->fs_shader))
            return false;
        m_effects[drawable->vs_shader] = drawable->effect;
    } else {
        drawable->effect = m_effects[drawable->vs_shader];
    };
    return true;
}


void RenderSystem::draw_all(mat3 projection) {
    for (auto &entity: *m_entities) {
        if (entity.drawable == nullptr || entity.clipped) {
            continue;
        }
        draw(entity, projection);
    }
    for (auto &tile : *m_tiles) {
        if (tile.second->clipped) {
            continue;
        }

        draw(*tile.second, projection);
    }
}

void RenderSystem::draw(Entity &entity, mat3 projection) {
        Drawable *drawable = entity.drawable;

        transform(entity);

        // Enabling alpha channel for textures
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);

        // Setting shaders
        glUseProgram(drawable->effect.program);

        // Getting uniform locations for glUniform* calls
        GLint transform_uloc = glGetUniformLocation(drawable->effect.program, "transform");
        GLint color_uloc = glGetUniformLocation(drawable->effect.program, "fcolor");
        GLint projection_uloc = glGetUniformLocation(drawable->effect.program, "projection");
        GLint offset_uloc = glGetUniformLocation(drawable->effect.program, "offset");
        GLint frames_uloc= glGetUniformLocation(drawable->effect.program, "frames");

        // Setting vertices and indices
        glBindVertexArray(drawable->vao);
        glBindBuffer(GL_ARRAY_BUFFER, drawable->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable->ibo);

        // Input data location as in the vertex buffer
        GLint in_position_loc = glGetAttribLocation(drawable->effect.program, "in_position");
        GLint in_texcoord_loc = glGetAttribLocation(drawable->effect.program, "in_texcoord");
        glEnableVertexAttribArray(in_position_loc);
        glEnableVertexAttribArray(in_texcoord_loc);
        glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) 0);
        glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) sizeof(vec3));

        // Enabling and binding texture to slot 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, drawable->texture->id);

        // Setting uniform values to the currently bound program
        glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *) &drawable->transform);
        float color[] = {1.f, 1.f, 1.f};
        glUniform3fv(color_uloc, 1, color);
        if (entity.animatable) {
            int rows = entity.animatable->num_rows;
            int cols = entity.animatable->num_columns;
            float frames[] = {(float) cols, (float) rows};
            float offset[] = {entity.animatable->frame_index.x / cols, entity.animatable->frame_index.y / rows};
            glUniform2fv(offset_uloc, 1, offset);
            glUniform2fv(frames_uloc, 1, frames);
        }
        glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *) &projection);

        // Drawing!
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

        glDisableVertexAttribArray(in_position_loc);
        glDisableVertexAttribArray(in_texcoord_loc);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //reset uniform transform
}

void RenderSystem::drawModal(mat3 projection, Modal &entity) {
    Drawable *drawable = entity.drawable;

    transform(entity);

    // Enabling alpha channel for textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // Setting shaders
    glUseProgram(drawable->effect.program);

    // Getting uniform locations for glUniform* calls
    GLint transform_uloc = glGetUniformLocation(drawable->effect.program, "transform");
    GLint color_uloc = glGetUniformLocation(drawable->effect.program, "fcolor");
    GLint projection_uloc = glGetUniformLocation(drawable->effect.program, "projection");

    // Setting vertices and indices
    glBindVertexArray(drawable->vao);
    glBindBuffer(GL_ARRAY_BUFFER, drawable->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable->ibo);

    // Input data location as in the vertex buffer
    GLint in_position_loc = glGetAttribLocation(drawable->effect.program, "in_position");
    GLint in_texcoord_loc = glGetAttribLocation(drawable->effect.program, "in_texcoord");
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_texcoord_loc);
    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) 0);
    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) sizeof(vec3));

    // Enabling and binding texture to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, drawable->texture->id);

    // Setting uniform values to the currently bound program
    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *) &drawable->transform);
    float color[] = {1.f, 1.f, 1.f};
    glUniform3fv(color_uloc, 1, color);
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *) &projection);

    // Drawing!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

    glDisableVertexAttribArray(in_position_loc);
    glDisableVertexAttribArray(in_texcoord_loc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //reset uniform transform
}

namespace {
    bool gl_compile_shader(GLuint shader) {
        glCompileShader(shader);
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
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

bool RenderSystem::load_from_file(Drawable::Effect &effect, const char *vs_path, const char *fs_path) {
    gl_flush_errors();

    // Opening files
    std::ifstream vs_is(vs_path);
    std::ifstream fs_is(fs_path);

    if (!vs_is.good() || !fs_is.good()) {
        fprintf(stderr, "Failed to load shader files %s, %s", vs_path, fs_path);
        return false;
    }

    // Reading sources
    std::stringstream vs_ss, fs_ss;
    vs_ss << vs_is.rdbuf();
    fs_ss << fs_is.rdbuf();
    std::string vs_str = vs_ss.str();
    std::string fs_str = fs_ss.str();
    const char *vs_src = vs_str.c_str();
    const char *fs_src = fs_str.c_str();
    GLsizei vs_len = (GLsizei) vs_str.size();
    GLsizei fs_len = (GLsizei) fs_str.size();

    effect.vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(effect.vertex, 1, &vs_src, &vs_len);
    effect.fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(effect.fragment, 1, &fs_src, &fs_len);

    // Compiling
    // Shaders already delete if compilation fails
    if (!gl_compile_shader(effect.vertex))
        return false;

    if (!gl_compile_shader(effect.fragment)) {
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
        if (is_linked == GL_FALSE) {
            GLint log_len;
            glGetProgramiv(effect.program, GL_INFO_LOG_LENGTH, &log_len);
            std::vector<char> log(log_len);
            glGetProgramInfoLog(effect.program, log_len, &log_len, log.data());

            release(effect);
            fprintf(stderr, "Link error: %s", log.data());
            return false;
        }
    }

    if (gl_has_errors()) {
        release(effect);
        fprintf(stderr, "OpenGL errors occured while compiling Effect");
        return false;
    }

    return true;
}

void RenderSystem::release(Drawable::Effect &effect) {
    glDeleteProgram(effect.program);
    glDeleteShader(effect.vertex);
    glDeleteShader(effect.fragment);
}

void RenderSystem::transform(Entity &entity) {
    out = {{1.f, 0.f, 0.f},
           {0.f, 1.f, 0.f},
           {0.f, 0.f, 1.f}};
    translate(out, entity.position);
    rotate(out, entity.radians);
    scale(out, entity.scale);
    entity.drawable->transform = out;
}

void RenderSystem::rotate(mat3 &out, float radians) {
    float c = cosf(radians);
    float s = sinf(radians);
    mat3 R = {{c,   s,   0.f},
              {-s,  c,   0.f},
              {0.f, 0.f, 1.f}};
    out = mul(out, R);
}

void RenderSystem::translate(mat3 &out, vec2 offset) {
    mat3 T = {{1.f,      0.f,      0.f},
              {0.f,      1.f,      0.f},
              {offset.x, offset.y, 1.f}};
    out = mul(out, T);
}

void RenderSystem::scale(mat3 &out, vec2 scale) {
    mat3 S = {{scale.x, 0.f,     0.f},
              {0.f,     scale.y, 0.f},
              {0.f,     0.f,     1.f}};
    out = mul(out, S);
}


void RenderSystem::update(float ms) {
    for (auto &entity : *m_entities) {
        if (!entity.animatable) {
            continue;
        }
        if (entity.flyable){
            entity.animatable->countdown -= ms;
            if (entity.animatable->countdown > 0) {
                continue;
            }
            entity.animatable->countdown = entity.animatable->frame_switch_time;
            entity.animatable->frame_index.x++;
            if (entity.animatable->frame_index.x == 6){
                entity.animatable->frame_index.x = 0;
            }
        } else if (entity.physics->velocity.x == 0) {
            if(entity.is_facing_forward) {
                entity.animatable->frame_index = {0 , 1};
            } else {
                entity.animatable->frame_index = {0, 0};
            }
        } else {
            entity.animatable->countdown -= ms;
            if (entity.animatable->countdown > 0) {
                continue;
            }
            entity.animatable->countdown = entity.animatable->frame_switch_time;
            if (entity.physics->velocity.x > 0) {
                entity.animatable->frame_index.y = 1;
            } else {
                entity.animatable->frame_index.y = 0;
            }
            entity.animatable->frame_index.x++;
            if (entity.animatable->frame_index.x == 4)
                entity.animatable->frame_index.x = 0;
        }
    }
}
