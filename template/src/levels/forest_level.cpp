#include "forest_level.hpp"

ForestLevel::ForestLevel(bool unlocked) :
    Level(unlocked) {
}

ForestLevel::~ForestLevel() = default;

bool ForestLevel::init() {
    return Level::init_scene(m_tile_vec, m_texture_map);
}

void ForestLevel::update(float elapsed_time) {
    Level::update(elapsed_time);
}
