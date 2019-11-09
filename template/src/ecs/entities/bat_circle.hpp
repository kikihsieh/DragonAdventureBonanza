#pragma once

#include "entity.hpp"
#include <list>

struct BatCircle : public Entity {
    BatCircle(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 0.5f, 0.5f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;

        position = pos;
        
        //collider = new Collider();
        is_facing_forward = true;
        
        flyable = new Flyable();
        flyable->flyable_enemy = true;
        flyable->fly_mode = 3;
        
        
    }
};

