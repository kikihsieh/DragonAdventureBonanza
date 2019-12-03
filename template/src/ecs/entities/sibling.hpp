#pragma once

#include "entity.hpp"

struct Sibling : public Entity {
    Sibling(std::shared_ptr<Texture> texture, vec2 pos, vec2 dir, vec2 texture_scale, int hp) {
        //scale = texture_scale;
        scale = { texture_scale.x*0.3f, texture_scale.y * 1.5f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("animated.fs.glsl");
        drawable->vs_shader = shader_path("animated.vs.glsl");
        drawable->texture = texture;

        health = new Health();
        health->health = hp;

        position = pos;

        physics = new Physics();
        physics->gravity = 0;
        physics->walk_speed = 200.f;
        physics->jump_speed = 0.f;

        physics->velocity = { dir.x * physics->walk_speed, dir.y * physics->walk_speed};
        physics->acceleration = { 0.f, physics->gravity };

        is_minion = true;

        collider = new Collider();
        is_facing_forward = false;
        
        animatable = new Animatable();
        animatable->num_rows = 1;
        animatable->num_columns = 5;
        animatable->frame_index = {0, 0};
    }
};
