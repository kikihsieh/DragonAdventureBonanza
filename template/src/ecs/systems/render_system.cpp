#define _USE_MATH_DEFINES
#include "render_system.hpp"
#include <vector>
#include <list>
#include <sstream>
#include <cmath>
#include <ecs/entities/tile.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <SDL_opengl.h>
#include <algorithm>

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {
    for (auto &shader : m_effects) {
        glDeleteShader(shader.second.vertex);
        glDeleteShader(shader.second.fragment);
        glDeleteProgram(shader.second.program);
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
    for (Entity &button: *m_buttons) {
        if (!button.drawable) {
            continue;
        }
        glDeleteBuffers(1, &button.drawable->vbo);
        glDeleteBuffers(1, &button.drawable->ibo);
        glDeleteVertexArrays(1, &button.drawable->vao);
    }

    for (auto &ch : characters) {
        glDeleteTextures(1, &ch.second.textureID);
    }

    glDeleteBuffers(1, &characters_drawable->vbo);
    glDeleteVertexArrays(1, &characters_drawable->vao);

    delete characters_drawable;
}

bool RenderSystem::init(std::list<Entity> *entities, std::map<int, Tile *> *tiles, std::list<Button> *buttons, std::list<Tile*> *lights) {
    m_effects = {};
    entities->sort([](const Entity & a, const Entity & b) { return a.depth > b.depth;});
//    std::sort(entities->begin(), entities->end(), [](Entity a, Entity b) { return a.depth < b.depth;});
    m_entities = entities;
    m_buttons = buttons;
    m_lights = lights;

    for (auto &entity : *entities) {
        if (entity.drawable == nullptr) {
            continue;
        }
        init_entity(entity);
    }
    for (auto &button : *buttons) {
        if (button.drawable == nullptr) {
            continue;
        }
        init_entity(button);
    }
    m_tiles = tiles;
    for (auto &tile : *m_tiles) {
        if (tile.second->drawable == nullptr) {
            continue;
        }
        init_entity(*tile.second);
    }
    return setup_freetype();
}

// https://learnopengl.com/In-Practice/Text-Rendering
bool RenderSystem::setup_freetype() {

    if (FT_Init_FreeType(&library))
        fprintf(stderr, "Failed to init Freetype library");

    if (FT_New_Face(library, PROJECT_SOURCE_DIR "/data/Kenney_Pixel.ttf", 0, &face))
        fprintf(stderr, "Font file could not be opened or read, or that it is broken");

    FT_Set_Pixel_Sizes(face, 0, 36);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            fprintf(stderr, "Failed to load Glyph");
            continue;
        }
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // Destroy FreeType when we are finished
    FT_Done_Face(face);
    FT_Done_FreeType(library);

    characters_drawable = new Drawable();
    characters_drawable->fs_shader = shader_path("text.fs.glsl");
    characters_drawable->vs_shader = shader_path("text.vs.glsl");

    glGenVertexArrays(1, &characters_drawable->vao);
    glGenBuffers(1, &characters_drawable->vbo);
    glBindVertexArray(characters_drawable->vao);
    glBindBuffer(GL_ARRAY_BUFFER, characters_drawable->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (gl_has_errors())
        return false;

    if (m_effects.find(characters_drawable->vs_shader) == m_effects.end()) {
        if (!load_from_file(characters_drawable->effect, characters_drawable->vs_shader,
                            characters_drawable->fs_shader))
            return false;
        m_effects[characters_drawable->vs_shader] = characters_drawable->effect;
    } else {
        characters_drawable->effect = m_effects[characters_drawable->vs_shader];
    }
    return true;
}

bool RenderSystem::init_entity(Entity &entity) {
    Drawable *drawable = entity.drawable;
    if (!entity.drawable->texture->is_valid()) {

        if (!entity.drawable->texture->load_from_file(entity.drawable->texture_path)) {
            fprintf(stderr, "Failed to load %s texture!", entity.drawable->texture_path);
            return false;
        }
    }

    entity.texture_size = {drawable->texture->width * 1.f, drawable->texture->height * 1.f};

    if (entity.animatable) {
        entity.texture_size = mul(entity.texture_size,
                                  {1.f / entity.animatable->num_columns, 1.f / entity.animatable->num_rows});
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
    }
    return true;
}

void RenderSystem::draw_all(mat3 projection) {
    // HACK: rendering background first for alpha in tiles to display properly. This is only working because
    //       we always put the background in the beginning of the list. I know it's not great...
    draw(m_entities->front(), projection);

    for (auto &tile : *m_tiles) {
        if (tile.second->clipped || !tile.second->drawable) {
            continue;
        }

        draw(*tile.second, projection);
    }
    float health = 0.f;
    for (auto &entity: *m_entities) {
        if (entity.drawable == nullptr || entity.clipped) {
            continue;
        }
        draw(entity, projection);
        if (!entity.player_tag)
            continue;
        health = entity.health->health;
    }
    for (auto &button: *m_buttons) {
        if (button.drawable == nullptr || button.clipped) {
            continue;
        }
        draw(button, projection);
    }
    draw_health(projection, health);
}

void RenderSystem::draw(Entity &entity, mat3 projection) {
    Drawable *drawable = entity.drawable;

    transform(entity);

    // Enabling alpha channel for textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (entity.useDepth) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
    else {
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    }

    // Setting shaders
    glUseProgram(drawable->effect.program);

    // Getting uniform locations for glUniform* calls
    GLint transform_uloc = glGetUniformLocation(drawable->effect.program, "transform");
    GLint color_uloc = glGetUniformLocation(drawable->effect.program, "fcolor");
    GLint projection_uloc = glGetUniformLocation(drawable->effect.program, "projection");
    GLint offset_uloc = glGetUniformLocation(drawable->effect.program, "offset");
    GLint frames_uloc = glGetUniformLocation(drawable->effect.program, "frames");
    GLint invinc_uloc = glGetUniformLocation(drawable->effect.program, "invicibility");
    GLint depth_uloc = glGetUniformLocation(drawable->effect.program, "level");
    GLint player_uloc = glGetUniformLocation(drawable->effect.program, "player");
    GLint lights_uloc = glGetUniformLocation(drawable->effect.program, "lights");
    GLint nlights_uloc = glGetUniformLocation(drawable->effect.program, "numLights");
    GLint flicker_uloc = glGetUniformLocation(drawable->effect.program, "flicker");

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
    glUniformMatrix4fv(transform_uloc, 1, GL_FALSE, (float *) &drawable->transform);
    float color[] = {1.f, 1.f, 1.f};
    glUniform3fv(color_uloc, 1, color);
    if(entity.is_background)
        glUniform1f(depth_uloc, entity.level);
    if (!entity.useDepth) {
        glUniform2fv(player_uloc, 1, (GLfloat *) &player_pos);
        glUniform1i(nlights_uloc, m_light_pos.size());
        if (m_light_pos.size() > 0) {
            glUniform2fv(lights_uloc, m_light_pos.size(), (GLfloat *) &m_light_pos[0]);
            glUniform1fv(flicker_uloc, m_flicker.size(), &m_flicker[0]);
        }
    }

    if (entity.animatable) {
        int rows = entity.animatable->num_rows;
        int cols = entity.animatable->num_columns;
        float frames[] = {(float) cols, (float) rows};
        float offset[] = {entity.animatable->frame_index.x / cols, entity.animatable->frame_index.y / rows};
        glUniform2fv(offset_uloc, 1, offset);
        glUniform2fv(frames_uloc, 1, frames);
    }
    if (entity.health) {
        glUniform1f(invinc_uloc, entity.health->invincible_timer);
    }
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *) &projection);

    // Drawing!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

    glDisableVertexAttribArray(in_position_loc);
    glDisableVertexAttribArray(in_texcoord_loc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //reset uniform transform
}

void RenderSystem::draw_modal(mat3 projection, Modal &entity) {
    Drawable *drawable = entity.drawable;

    transform(entity);

    // Enabling alpha channel for textures
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);

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
    glUniformMatrix4fv(transform_uloc, 1, GL_FALSE, (float *) &drawable->transform);
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

void RenderSystem::draw_health(mat3 projection, int health) {
    if (!health)
        return;
    std::string string = "HEALTH: " + std::to_string(health);

    float screen_width = 1200.f;
    float screen_height = 800.f;
    float offset = 50.f;

    vec2 position = {screen_width * projection.c2.x / -2.0f - (screen_width - offset) / 2.f,
                     screen_height * projection.c2.y / 2.0f - (screen_height - offset) / 2.f};
    glm::vec3 color = {1.0, 1.0, 1.0};

    render_text(string, projection, position, color);
}

void RenderSystem::render_text(std::string text, mat3 projection, vec2 position, glm::vec3 color, float scale) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);

    glUseProgram(characters_drawable->effect.program);

    GLint projection_uloc = glGetUniformLocation(characters_drawable->effect.program, "projection");

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(characters_drawable->vao);

    std::string::const_iterator it;
    for (it = text.begin(); it != text.end(); it++) {
        Character ch = characters[*it];

        // bottom left of the character
        GLfloat xpos = position.x + ch.bearing.x * scale;
        GLfloat ypos = position.y + (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        GLfloat vertices[6][4] = {
                {xpos,     ypos - h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos - h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos - h, 1.0, 0.0}
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, characters_drawable->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUniform3f(glGetUniformLocation(characters_drawable->effect.program, "textColor"), color.x, color.y, color.z);
        glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *) &projection);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        position.x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderSystem::render_text(std::string text, mat3 projection, vec2 position, glm::vec3 color) {
    render_text(text, projection, position, color, 1.f);
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
    out = glm::mat4(1.f);
    out = glm::translate(out, glm::vec3(entity.position.x, entity.position.y, entity.depth));
    out = glm::rotate(out, entity.radians, glm::vec3(0.f, 0.f, 1.f));
    out = glm::scale(out, glm::vec3(entity.scale.x, entity.scale.y, 1.f));
    entity.drawable->transform = out;
}

//void RenderSystem::rotate(mat3 &out, float radians) {
//    float c = cosf(radians);
//    float s = sinf(radians);
//    mat3 R = {{c,   s,   0.f},
//              {-s,  c,   0.f},
//              {0.f, 0.f, 1.f}};
////              {0.f, 0.f, 0.f, 1.f}};
//    out = mul(out, R);
//}
//
//void RenderSystem::translate(mat3 &out, vec2 offset, float depth) {
//    mat3 T = {{1.f,      0.f,      0.f},
//              {0.f,      1.f,      0.f},
////              {0.f,      0.f,      1.f,    0.f},
//              {offset.x, offset.y, 1.f}};
//    out = mul(out, T);
//}
//
//void RenderSystem::scale(mat3 &out, vec2 scale) {
//    mat3 S = {{scale.x, 0.f,     0.f},
//              {0.f,     scale.y, 0.f},
//              {0.f,     0.f,     1.f}};
////              {0.f,     0.f,     0.f,   1.f}};
//    out = mul(out, S);
//}


void RenderSystem::update(float ms) {
    m_light_pos.clear();
    m_flicker.clear();
    for (auto &entity : *m_entities) {
        if (!entity.animatable || entity.is_boss_proj || entity.is_bomb) {
            continue;
        }
        if (entity.player_tag)
        {
            player_pos = entity.position;
        }
        if (entity.flyable) {
            entity.animatable->countdown -= ms;
            if (entity.animatable->countdown > 0) {
                continue;
            }
            entity.animatable->countdown = entity.animatable->frame_switch_time;
            entity.animatable->frame_index.x++;
            if (entity.animatable->frame_index.x == 6) {
                entity.animatable->frame_index.x = 0;
            }
        } else if (entity.physics->velocity.x == 0 && entity.health->is_player && entity.animatable->num_rows > 1) {
            if (entity.is_facing_forward) {
                entity.animatable->frame_index = {0, 1};
            } else {
                entity.animatable->frame_index = {0, 0};
            }
        } else {
            entity.animatable->countdown -= ms;
            if (entity.animatable->countdown > 0) {
                continue;
            }
            entity.animatable->countdown = entity.animatable->frame_switch_time;
            if (entity.is_facing_forward && entity.animatable->num_rows > 1) {
                entity.animatable->frame_index.y = 1;
            } else {
                entity.animatable->frame_index.y = 0;
            }
            entity.animatable->frame_index.x++;
            if (entity.animatable->frame_index.x == entity.animatable->num_columns)
                entity.animatable->frame_index.x = 0;
        }
    }
    for (auto &light: *m_lights) {
        if(light->properties->lit) {
            m_light_pos.emplace_back(light->position);
            light->animatable->countdown -= ms;
            light->properties->countdown += ms;
            if (light->properties->countdown > 10000000000.f)
                light->properties->countdown = 0.f;
            m_flicker.emplace_back(light->properties->countdown);
            if (light->animatable->countdown > 0) {
                continue;
            }
            light->animatable->countdown = light->animatable->frame_switch_time;
            light->animatable->frame_index.x++;
            if (light->animatable->frame_index.x == light->animatable->num_columns)
                light->animatable->frame_index.x = 0;
        }
    }
    for (auto &tile: *m_tiles) {
        if(tile.second->clipped || !tile.second->animatable){
            continue;
        }
        tile.second->animatable->countdown -= ms;
        if (tile.second->animatable->countdown > 0) {
            continue;
     }
        tile.second->animatable->countdown = tile.second->animatable->frame_switch_time;
        tile.second->animatable->frame_index.x++;
        if (tile.second->animatable->frame_index.x == tile.second->animatable->num_columns)
            tile.second->animatable->frame_index.x = 0;
     }

}
