#pragma once

#include "common.hpp"
#include <vector>
#include <stdio.h>

#include <ecs/entities/entity.hpp>

class Tile : public Entity
{
public:
    Tile();
    ~Tile();

    // Creates all the associated render resources and default transform
    bool init();
    
    void set_position(float x, float y);
    
//    void compute_world_coordinate();

    void set_texture(Texture *texture) {
        drawable->texture = texture;
    }
};
