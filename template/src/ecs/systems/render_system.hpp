#pragma once
#include "common.hpp"
#include <vector>
#include <map>
#include "../entities/entity.hpp"

class RenderSystem {
public:
	RenderSystem();
	~RenderSystem();

	bool init(const std::vector<Entity> &entities);
	void destroy();
	void draw(mat3 projection);

private:
    bool load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path);

    void transform(Entity &entity);
    void rotate(mat3 &out, float radians);
    void translate(mat3 &out, vec2 offset);
    void scale(mat3 &out, vec2 scale);

    void release(Drawable::Effect& effect);
    std::vector<Entity> m_entities;
    std::map<const char*, Drawable::Effect> m_effects;
};