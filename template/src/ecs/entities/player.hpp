#pragma once

#include "entity.hpp"
#include <list>

struct Player : public Entity {
    Player() {
        scale = {0.5f, 0.5f};
        position = { 100.f, 550.f };

        physics = new Physics();
        physics->gravity = 750.f;
        physics->walk_speed = 250.f;
        physics->jump_speed = -430.f;
        physics->velocity = {physics->walk_speed, 0.f};
        physics->acceleration = {0.f, physics->gravity};

        drawable = new Drawable();
        drawable->texture_path = textures_path("initial.png");
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");

        airdash = new AirDash();
        shooting = new Shooting();

        collider = new Collider();

        input = new Input();

        player_tag = true;
        is_facing_forward = true;
        is_player_proj = false;
        is_enemy_proj = false;

        const TexturePathMapping m_texture_map = {
                { 0, textures_path("initial.png")},
                { 1, textures_path("move1.png")},
                { 2, textures_path("move2.png")},
                { 3, textures_path("move3.png")},
                { -1, textures_path("initial-1.png")},
                { -2, textures_path("move-1.png")},
                { -3, textures_path("move-2.png")},
                { -4, textures_path("move-3.png")},
        };
        animatable = new Animatable(m_texture_map);
    }
};
