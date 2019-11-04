#pragma once

#include "entity.hpp"

struct Bat : public Entity {
    Bat(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;

        position = pos;
        /*
        collider = new Collider();
        is_facing_forward = true;
        */
        flyable = new Flyable();
        flyable->flyable_enemy = true;
        
        enemyai = new EnemyAI();
        
        
    }
};
