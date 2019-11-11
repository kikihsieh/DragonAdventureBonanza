#pragma once

#include <vector>

#include "entity.hpp"

struct Tile : public Entity {
    struct Properties {
        Properties() : bounce(0.f), friction(0.f) {}
        Properties(float bounce, float friction) : bounce(bounce), friction(friction) {}

        float bounce;
        float friction;
    };

    void destroy() override {
        delete properties;
        Entity::destroy();
    }


    Tile(std::shared_ptr<Texture> texture, vec2 pos, vec2 scale, vec2 size) {
        this->scale = scale;

        drawable = new Drawable();
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;  

        texture->height = size.y;
        texture->width = size.x;
        position = pos;

        properties = new Tile::Properties();
    }

    Tile(std::shared_ptr<Texture> texture, vec2 pos, vec2 scale, vec2 size, Properties* properties)
        : Tile(texture, pos, scale, size) {
        delete this->properties;
        this->properties = properties;
    }

    Properties* properties;
};
