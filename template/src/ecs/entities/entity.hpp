#pragma once

#include "../components/collider.hpp"
#include "../components/drawable.hpp"
#include "../components/physics.hpp"
#include "../components/input.hpp"
#include "../components/enemyAI.hpp"
#include "../components/animatable.hpp"


struct Entity {
    Entity() :
        physics(nullptr),
        enemyai(nullptr),
        drawable(nullptr),
        collider(nullptr),
        input(nullptr),
        animatable(nullptr),
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
    EnemyAI *enemyai;
	Drawable* drawable;
	Collider* collider;
    Input* input;
    Animatable* animatable;

	float radians;
	vec2 position;
	vec2 scale;

    bool is_facing_forward;
};
