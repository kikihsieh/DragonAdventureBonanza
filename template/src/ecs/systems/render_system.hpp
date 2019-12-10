#pragma once
#include "common.hpp"
#include <list>
#include <map>
#include <ecs/entities/modal.hpp>
#include <ecs/entities/tile.hpp>
#include "../entities/entity.hpp"
#include <ecs/components/drawable.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class RenderSystem {
public:
	RenderSystem();
	~RenderSystem();

    struct Character {
        GLuint textureID;
        glm::ivec2 size;
        glm::ivec2 bearing;
        GLuint advance;
    };

    bool init(std::list<Entity>* entities, std::map<int, Tile*>* tiles, std::list<Button>* buttons, std::list<Tile*>* lights);
    bool init_entity(Entity& entity);
    bool setup_freetype();

	void draw_all(mat3 projection);
	void draw(Entity &entity, mat3 projection);
	void draw_modal(mat3 projection, Modal& entity);
    void draw_health(mat3 projection, int health);
    void render_text(std::string text, mat3 projection, vec2 position, glm::vec3 color);
    void render_text(std::string text, mat3 projection, vec2 position, glm::vec3 color, float scale);
	void update(float ms);

private:
    bool load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path);

    void transform(Entity &entity);
    void rotate(mat3 &out, float radians);
    void translate(mat3 &out, vec2 offset, float level);
    void scale(mat3 &out, vec2 scale);

    void release(Drawable::Effect& effect);

    Drawable* characters_drawable;

    FT_Library library;
    FT_Face face;

    std::list<Entity>* m_entities;
	std::list<Button>* m_buttons;
	std::list<Tile*>* m_lights;
	std::vector<vec2> m_light_pos;
	std::vector<float> m_flicker;
    std::map<int, Tile*>* m_tiles;
    std::map<const char*, Drawable::Effect> m_effects;
    std::map<GLchar, Character> characters;
    glm::mat4 out;
    vec2 player_pos;
};
