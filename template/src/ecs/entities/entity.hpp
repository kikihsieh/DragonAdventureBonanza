#pragma once

#include <ecs/components/airdash.hpp>
#include "../components/collider.hpp"
#include "../components/drawable.hpp"
#include "../components/physics.hpp"
#include "../components/input.hpp"
#include "../components/enemyAI.hpp"

struct Entity {
    Entity() :
        physics(nullptr),
        enemyai(nullptr),
        drawable(nullptr),
        collider(nullptr),
        input(nullptr),
        airdash(nullptr),
        radians(0.f),
        position({0.f, 0.f}),
        scale({1.f, 1.f}),
        is_facing_forward(false) {
    }

    ~Entity() {}

    /** Before permanently deleting an enemy, you must call destroy!
        Cannot be in destructor because we do not want these objects deleted when being moved or copied! **/
    void destroy() {
        delete physics;
        delete collider;
        delete input;
        delete airdash;
        delete drawable;
    }

    // Components
	Physics *physics;
    EnemyAI *enemyai;
	Drawable* drawable;
	Collider* collider;
    Input* input;
	AirDash* airdash;

	float radians;
	vec2 position;
	vec2 scale;

    bool is_facing_forward;
};
