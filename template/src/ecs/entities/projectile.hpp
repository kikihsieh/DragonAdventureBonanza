#pragma once

#include "entity.hpp"

struct Projectile : public Entity {
    Projectile(std::shared_ptr<Texture> texture, vec2 pos, vec2 dir, vec2 texture_scale, bool isEnemy) {
        scale = texture_scale;
        if (!isEnemy) {
            scale.x *=1.3;
            scale.y *= 1.5;
        }

        drawable = new Drawable();
        drawable->fs_shader = shader_path("animated.fs.glsl");
        drawable->vs_shader = shader_path("animated.vs.glsl");
        drawable->texture = texture;
        
        animatable = new Animatable();
        animatable->num_columns = 1;
        animatable->num_rows = 1;
        animatable->frame_index = {0,0};
        
    
        position = pos;
        
        is_player_proj = !isEnemy;
        is_enemy_proj = isEnemy;
        
        physics = new Physics();
        physics->gravity = (isEnemy) ? 650.f : 0.f;
        physics->walk_speed = (isEnemy) ? 350.f : 500.f;
        physics->jump_speed = 0.f;
        
        physics->velocity = { dir.x * physics->walk_speed, dir.y * physics->walk_speed};
        physics->acceleration = { 0.f, physics->gravity };

        properties = std::make_shared<Properties>(Properties::PROJECTILE);

        depth = -0.98f;
        clipped = false;

        collider = new Collider();
        is_facing_forward = true;
    }
};
