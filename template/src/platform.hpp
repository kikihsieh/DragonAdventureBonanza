#pragma once

#include "common.hpp"
#include <vector>


class Platform : public Entity
{
public:
    
    // Creates all the associated render resources and default transform
    bool init();
    
    // Releases all associated resources
    void destroy();
    
    // Renders the background
    void draw(const mat3& projection)override;
    
    // Returns the current platform position
    vec2 get_position() const;
    
    vec2 get_bounding_box() const;
    
    void compute_world_coordinate();
    
    float top;
    float bottom;
    float left;
    float right;
    
private:
    Texture platform_med_texture;
    TexturedVertex vertices[4];
    std::vector<vec2> platform_world_coord;
};
