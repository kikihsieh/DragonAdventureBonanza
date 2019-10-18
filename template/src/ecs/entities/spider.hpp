#pragma once
#include "entity.hpp"

struct Spider : public Entity {
    Spider(Texture* texture, int col, int row) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;  

        position.x = col * texture->width*scale.x - texture->width*0.5f*scale.x;
        position.y = row * texture->height*scale.y + texture->height*0.5f*scale.y;
    }
};
