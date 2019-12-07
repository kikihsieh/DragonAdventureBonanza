#pragma once

#include "entity.hpp"

struct Projectile : public Entity {
    Projectile(std::shared_ptr<Texture> texture, vec2 pos, vec2 dir, vec2 texture_scale, bool isEnemy) {
        scale = texture_scale;
        if (!isEnemy) {
            scale = mul(scale, 1.3f);
        }

        drawable = new Drawable();
        drawable->fs_shader = shader_path("projectile.fs.glsl");
        drawable->vs_shader = shader_path("projectile.vs.glsl");
        drawable->texture = texture;
        
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

        collider = new Collider();
        is_facing_forward = true;
    }
};
