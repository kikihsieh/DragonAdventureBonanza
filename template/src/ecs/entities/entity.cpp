#include "entity.hpp"

int Entity::current_id = 0;

Entity::Entity() :
        id(current_id++),
        physics(nullptr),
        enemyai(nullptr),
        drawable(nullptr),
        collider(nullptr),
        input(nullptr),
        airdash(nullptr),
        animatable(nullptr),
        health(nullptr),
        shooting(nullptr),
        flyable(nullptr),
        properties(nullptr),
        radians(0.f),
        position({0.f, 0.f}),
        scale({1.f, 1.f}),
        is_facing_forward(false),
        player_tag(false),
        is_player_proj(false),
        is_enemy_proj(false),
        is_boss_proj(false),
        is_minion(false),
        is_bomb(false),
        is_background(false),
        clipped(true) {
}

void Entity::destroy() {
    delete physics;
    delete collider;
    delete input;
    delete airdash;
    delete enemyai;
    delete drawable;
    delete animatable;
    delete health;
    delete shooting;
    delete flyable;
}

