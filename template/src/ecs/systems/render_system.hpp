#pragma once
#include "common.hpp"
#include <vector>
#include <map>
#include "../entities/entity.hpp"

class RenderSystem
{
public:
	enum entity_types {
		//add to here when adding sprites
		PLAYER,
		FOREST_BACKGROUND,
		CAVE_BACKGROUND,
		START_MENU_BACKGROUND,
		TILE,
		SPIDER,
		BOSS1,
		BOSS2,
		BOSS3,
		BOSS4,
		BOSS5
	};

	RenderSystem();
	~RenderSystem();

	virtual bool init(const std::vector<Entity*> &entities);
	virtual void destroy(const std::vector<Entity*> &entities);
	virtual void draw(const mat3& projection, const std::vector<Entity*> &entities);

private:
	std::map<entity_types, const char*> entity_textures;
	std::map<entity_types, const char*> vs_shader_types;
	std::map<entity_types, const char*> fs_shader_types;
};