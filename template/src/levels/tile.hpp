#pragma once

#include "common.hpp"
#include <vector>
#include <stdio.h>

class Tile : public Entity
{
public:
    ~Tile();

    // Creates all the associated render resources and default transform
    bool init();
    
    // Releases all associated resources
    void destroy();
    
    // Renders the background
    void draw(const mat3& projection)override;
    
    void set_position(float x, float y);
    
    void compute_world_coordinate();

    void set_texture(Texture *texture) {
        m_texture = texture;
    }
    
    float top;
    float bottom;
    float left;
    float right;
    
private:
    Texture * m_texture;

private:
    //todo GLint
    TexturedVertex vertices[4];
    std::vector<vec2> platform_world_coord;
};
