#pragma once

#include "../components/collider.hpp"
#include "../components/drawable.hpp"
#include "../components/physics.hpp"
#include "../components/input.hpp"
#include "../components/health.hpp"

struct Entity {
    Entity() :
        physics(nullptr),
        drawable(nullptr),
        collider(nullptr),
        input(nullptr),
        radians(0.f),
        position({0.f, 0.f}),
        scale({1.f, 1.f}),
        is_facing_forward(false) {
    }

    ~Entity() {
        // TODO Fix memory leaks. Cannot simply delete here because after inserting into list,
        //  destructor is called and left with dangling pointer
//        delete physics;
//        delete drawable;
//        delete collider;
//        delete input;
    }

    // Components
	Physics *physics;
	Drawable* drawable;
	Collider* collider;
    Input* input;
	Health* health;

	float radians;
	vec2 position;
	vec2 scale;

    bool is_facing_forward;
};