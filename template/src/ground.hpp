#pragma once

#include "common.hpp"


class Ground : public Entity
{
public:

    // Creates all the associated render resources and default transform
    bool init();

    // Releases all associated resources
    void destroy();

    // Renders the background
    void draw(const mat3& projection)override;

private:
    Texture ground_texture;
};
