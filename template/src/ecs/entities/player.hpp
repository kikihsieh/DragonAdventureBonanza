#pragma once

#include <ecs/components/health.hpp>
#include "entity.hpp"
#include <list>

struct Player : public Entity {
    Player() {
        scale = {0.5f, 0.5f};

        physics = new Physics();
        physics->gravity = 750.f;
        physics->walk_speed = 250.f;
        physics->jump_speed = -450.f;
        physics->velocity = {0.f, 0.f};
        physics->acceleration = {0.f, physics->gravity};

        drawable = new Drawable();
        drawable->texture_path = textures_path("dragon_sprite.png");
        drawable->fs_shader = shader_path("player.fs.glsl");
        drawable->vs_shader = shader_path("player.vs.glsl");

        health = new Health();
        health->health = 10;
        health->is_player = true;

        collider = new Collider();

        input = new Input();

        shooting = new Shooting();
        shooting->time = 1000;

        player_tag = true;
        is_facing_forward = true;
        is_player_proj = false;
        is_enemy_proj = false;

        animatable = new Animatable();
        animatable->num_rows = 2;
        animatable->num_columns = 4;
        depth = -0.98f;

        clipped = false;
    }
};
