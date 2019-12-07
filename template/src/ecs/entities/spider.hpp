#pragma once

#include <ecs/components/health.hpp>
#include "entity.hpp"

struct Spider : public Entity {
    Spider(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("animated.fs.glsl");
        drawable->vs_shader = shader_path("animated.vs.glsl");
        drawable->texture = texture;
        
        animatable = new Animatable();
        animatable->num_columns = 1;
        animatable->num_rows = 1;
        animatable->frame_index = {0,0};
        
        health = new Health();
        health->health = 1;
        
        position = pos;

        physics = new Physics();
        physics->gravity = 750.f;
        physics->walk_speed = 50.f;
        
        physics->velocity = { physics->walk_speed, 0.f };
        physics->acceleration = { 0.f, physics->gravity };
        
        collider = new Collider();
        is_facing_forward = true;
        
        enemyai = new EnemyAI();
    }
};
