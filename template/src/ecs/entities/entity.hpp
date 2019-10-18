#pragma once

#include "../components/collider.hpp"
#include "../components/drawable.hpp"
#include "../components/physics.hpp"

struct Entity {
    Entity() :
        physics(nullptr),
        drawable(nullptr),
        collider(nullptr),
        radians(0.f),
        position({0.f, 0.f}),
        scale({1.f, 1.f}) {
    }

    // Components
	Physics *physics;
	Drawable* drawable;
	Collider* collider;

	float radians;
	vec2 position;
	vec2 scale;
};