#pragma once

#include "entity.hpp"

struct Spider : public Entity {
    Spider(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;

        position = pos;
    }
};
