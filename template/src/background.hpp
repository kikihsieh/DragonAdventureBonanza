#pragma once

#include "common.hpp"


class Background : public Entity
{
public:
	
	// Creates all the associated render resources and default transform
	bool init();

	// Releases all associated resources
	void destroy();

	// Renders the background
	void draw(const mat3& projection)override;

private:
	Texture background_texture;
};
