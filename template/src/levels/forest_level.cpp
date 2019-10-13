#include "forest_level.hpp"

ForestLevel::ForestLevel()
{
    Level::m_bg_texture_path = textures_path("background.png");
    Level::m_x_boundaries = {-200.f, 1000.f};
    Level::m_y_boundaries = {200.f, 700.f};
}

void ForestLevel::update() {
    Level::update();
}
