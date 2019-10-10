#pragma once

#include "common.hpp"
#include <vector>
#include <stdio.h>

class Tile : public Entity
{
    //TODO ask TA about changing the tiles
public:
    
    // Creates all the associated render resources and default transform
    bool init();
    
    // Releases all associated resources
    void destroy();
    
    // Renders the background
    void draw(const mat3& projection)override;
    
    void setPosition(float x, float y);
    
    void compute_world_coordinate();
    
    float top;
    float bottom;
    float left;
    float right;
    
    Texture * texture; //todo GLint
    
private:
    TexturedVertex vertices[4];
    std::vector<vec2> platform_world_coord;
};
