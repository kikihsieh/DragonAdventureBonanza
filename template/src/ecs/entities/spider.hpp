#pragma once

#include <ecs/components/health.hpp>
#include "entity.hpp"

struct Spider : public Entity {
    Spider(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;
        
        health = new Health();
        health->health = 1;
        
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
