#include <iostream>
#include "forest_level.hpp"

ForestLevel::ForestLevel(bool unlocked) :
    Level(textures_path("background.png"), unlocked) {
}

ForestLevel::~ForestLevel() = default;

bool ForestLevel::init() {
    return Level::init_textures(m_tile_vec, m_texture_map);
}

void ForestLevel::update() {
    Level::update();
}

