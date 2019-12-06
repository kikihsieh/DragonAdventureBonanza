#pragma once

#include "../components/airdash.hpp"
#include "../components/properties.hpp"
#include "../components/collider.hpp"
#include "../components/drawable.hpp"
#include "../components/physics.hpp"
#include "../components/input.hpp"
#include "../components/enemyAI.hpp"
#include "../components/animatable.hpp"
#include "../components/health.hpp"
#include "../components/shooting.hpp"
#include "../components/flyable.hpp"

struct Entity {
    Entity();
    ~Entity() {}

    /** Before permanently deleting an enemy, you must call destroy!
        Cannot be in destructor because we do not want these objects deleted when being moved or copied! **/
    void destroy();

    // Components
	Physics *physics;
    EnemyAI *enemyai;
	Drawable* drawable;
	Collider* collider;
    Input* input;
	AirDash* airdash;
    Animatable* animatable;
	Health* health;
    Shooting* shooting;
    Flyable* flyable;

    std::shared_ptr<Properties> properties;

	float radians;
	vec2 position;
	vec2 scale;
	vec2 texture_size;

    bool player_tag;
    bool is_facing_forward;
    bool is_player_proj;
    bool is_enemy_proj;
    bool is_boss_proj;
    bool is_minion;

    bool is_background;

    bool is_bomb;

    int id;
    float depth = -0.5;
    float level = 1.f;

    static int current_id;

    bool clipped;
    bool useDepth = true;
};
