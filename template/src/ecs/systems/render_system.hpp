#pragma once
#include "common.hpp"
#include <list>
#include <map>
#include "../entities/entity.hpp"

class RenderSystem {
public:
	RenderSystem();
	~RenderSystem();

	bool init(std::list<Entity>* entities);
    bool initEntity(Entity& entity);
    
	void destroy();
    void destroyEntity(Entity& entity);
    
	void draw(mat3 projection);
	void drawModal(mat3 projection, Entity& entity);
	void update(float ms);
    void update_entities(std::list<Entity>* entities);

private:
    bool load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path);

    void transform(Entity &entity);
    void rotate(mat3 &out, float radians);
    void translate(mat3 &out, vec2 offset);
    void scale(mat3 &out, vec2 scale);

    void release(Drawable::Effect& effect);
    std::list<Entity>* m_entities;
    std::map<const char*, Drawable::Effect> m_effects;
    mat3 out;
};
