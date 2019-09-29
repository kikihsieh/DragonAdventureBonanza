#pragma once

#include "common.hpp"
#include <vector>


class Ground : public Entity
{
public:

    // Creates all the associated render resources and default transform
    bool init();

    // Releases all associated resources
    void destroy();

    // Renders the background
    void draw(const mat3& projection)override;

	void set_surface_y();

	// The y coordinate of the ground landing surface
	float surface_y;

private:
    Texture ground_texture;
	TexturedVertex vertices[4];
};
