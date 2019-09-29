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
    
    float topSide;
    float bottomSide;
    float rightSide;
    float leftSide;
    
private:
    Texture platform_med_texture;
    TexturedVertex vertices[4];
};
