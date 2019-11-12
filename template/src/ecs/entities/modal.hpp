#pragma once

#include "entity.hpp"
#include "button.hpp"

struct Modal : public Entity {

    Modal(const char* texture_path) : Entity(){
        scale = {0.8f, 0.8f};
        position = {600.f, 400.f};

        drawable = new Drawable();
        drawable->texture_path = texture_path;
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
    }
};



