#pragma once

#include "common.hpp"
#include <vector>

// Salmon enemy 
class Enemy : public Entity
{
	// Shared between all enemies, no need to load one for each instance
	static Texture enemy_texture;

public:
	// Creates all the associated render resources and default transform
	bool init();

	// Releases all the associated resources
	void destroy();

	// Update enemy due to current
	// ms represents the number of milliseconds elapsed from the previous update() call
	void update(float ms);

	// Renders the salmon
	// projection is the 2D orthographic projection matrix
	void draw(const mat3& projection) override;

	// Returns the current enemy position
	vec2 get_position()const;

	// Sets the new enemy position
	void set_position(vec2 position);

	// Returns the enemy' bounding box for collision detection, called by collides_with()
	vec2 get_bounding_box() const;
};
