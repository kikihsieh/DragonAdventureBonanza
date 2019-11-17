#ifndef DAB_CLOUD_HPP
#define DAB_CLOUD_HPP

#include "entity.hpp"

struct Cloud : public Entity {
    Cloud(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 0.2f, 0.2f };
        texture_size = {(float) texture->width, (float) texture->height};

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;

        position = pos;

        position = pos;
        physics = new Physics();
        physics->gravity = 0;

        physics->velocity = { -20, 0.f };
    }
};

#endif //DAB_CLOUD_HPP
