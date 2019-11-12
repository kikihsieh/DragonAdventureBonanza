#pragma once

#include "entity.hpp"
#include <list>

struct Bat : public Entity {
    Bat(std::shared_ptr<Texture> texture, vec2 pos, int fly_mode) {
        scale = { 0.5f, 0.5f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("animated.fs.glsl");
        drawable->vs_shader = shader_path("animated.vs.glsl");
        drawable->texture = texture;

        position = pos;
        
        //collider = new Collider();
        is_facing_forward = true;

        flyable = new Flyable();
        flyable->flyable_enemy = true;
        flyable->fly_mode = fly_mode;

        collider = new Collider();
        animatable = new Animatable();
        animatable->num_rows = 1;
        animatable->num_columns = 6;
        animatable->frame_index = {0, 0};

        physics = new Physics();

        health = new Health();
        health->health = 1;
    }
};

