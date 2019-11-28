#ifndef DAB_FINAL_BOSS_HPP
#define DAB_FINAL_BOSS_HPP

#include "entity.hpp"

struct FinalBoss : public Entity {
    FinalBoss(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 0.35f, 0.35f };
        texture_size = {(float) texture->width, (float) texture->height};

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;

        position = pos;

        position = pos;
        physics = new Physics();
        physics->gravity = 0;
        physics->walk_speed = 30.f;

        physics->velocity = { 0, 0.f };
        physics->acceleration = { 0.f, physics->gravity };

        collider = new Collider();
        is_facing_forward = true;

        health = new Health();
        health->health = 200;
        health->is_boss = true;
        
        animatable = new Animatable();
        animatable->num_rows = 1;
        animatable->num_columns = 10;
    }
};

#endif //DAB_FINAL_BOSS_HPP
