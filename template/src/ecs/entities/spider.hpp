#pragma once

#include "entity.hpp"

struct Spider : public Entity {
    Spider(Texture* texture, vec2 pos) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;

        position = pos;
        
        position = pos;
        physics = new Physics();
        physics->gravity = 10.f;
        physics->walk_speed = 50.f;
        
        physics->velocity = { physics->walk_speed, 0.f };
        physics->acceleration = { 0.f, physics->gravity };
        
        collider = new Collider();
        is_facing_forward = true;
        
        enemyai = new EnemyAI();
    }
};
