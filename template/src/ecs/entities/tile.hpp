#pragma once

#include "common.hpp"
#include <vector>
#include <stdio.h>

#include <ecs/entities/entity.hpp>

struct Tile : public Entity {
    Tile(Texture* texture, int col, int row) {
        scale = { 0.75f, 0.75f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("background.fs.glsl");
        drawable->vs_shader = shader_path("background.vs.glsl");
        drawable->texture = texture;

        position.x = col * texture->width*scale.x - texture->width*0.5f*scale.x;
        position.y = row * texture->height*scale.y + texture->height*0.5f*scale.y;
    }
};
