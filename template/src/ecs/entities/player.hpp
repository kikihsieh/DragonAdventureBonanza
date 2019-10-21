#pragma once

#include "entity.hpp"
#include <list>

struct Player : public Entity {
    Player() {
        scale = {0.5f, 0.5f};
        position = {100.f, 300.f};

        physics = new Physics();
        physics->gravity = 10.f;
        physics->walk_speed = 250.f;
        physics->jump_speed = -500.f;
        physics->velocity = {physics->walk_speed, 0.f};
        physics->acceleration = {0.f, physics->gravity};

        drawable = new Drawable();
        drawable->texture_path = textures_path("initial.png");
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");

        collider = new Collider();
        input = new Input();
        is_facing_forward = true;
            const TexturePathMapping m_texture_map = {
                    { 0, textures_path("initial.png")},
                    { 1, textures_path("initial.png")},
                    { 2, textures_path("initial.png")},
                    { 3, textures_path("initial.png")},
                    { 4, textures_path("move1.png")},
                    { 5, textures_path("move1.png")},
                    { 6, textures_path("move1.png")},
                    { 7, textures_path("move1.png")},
                    { 8, textures_path("move2.png")},
                    { 9, textures_path("move2.png")},
                    { 10, textures_path("move2.png")},
                    { 11, textures_path("move2.png")},
                    { 12, textures_path("move3.png")},
                    { 13, textures_path("move3.png")},
                    { 14, textures_path("move3.png")},
                    { 15, textures_path("move3.png")},
            };
        animatable = new Animatable(m_texture_map);
//        animatable(m_texture_map);

    }


};
