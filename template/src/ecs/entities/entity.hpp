#pragma once

#include <ecs/components/drawable.hpp>
#include "../components/physics.hpp"
#include "common.hpp"

struct Entity {

    ~Entity() {
        delete physics;
        delete drawable;
    }

    // pointers to all components go here
	Physics *physics = nullptr;
	Drawable* drawable = nullptr;

	float radians = 0.f;
	vec2 position = {0,0};
	vec2 scale = {0,0};
};