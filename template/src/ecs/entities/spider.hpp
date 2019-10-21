#pragma once

#include <ecs/components/health.hpp>
#include "entity.hpp"

struct Spider : public Entity {
    Spider(Texture* texture, vec2 pos) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;
        
        health = new Health();
        health->health = 1;
        
        position = pos;
    }
};
