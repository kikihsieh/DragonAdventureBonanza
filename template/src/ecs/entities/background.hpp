#pragma once
#include "entity.hpp"

struct Background : public Entity {
    Background(const char* texture_path) : Entity() {
        drawable = new Drawable();
        drawable->texture_path = texture_path;
        drawable->fs_shader = shader_path("background.fs.glsl");
        drawable->vs_shader = shader_path("background.vs.glsl");

        clipped = false;

        is_background = true;

        depth = 0.f;
        level = 2.f;
    }
};
