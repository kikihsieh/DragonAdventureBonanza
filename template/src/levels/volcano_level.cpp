#include "volcano_level.hpp"

VolcanoLevel::VolcanoLevel(bool unlocked) :
        Level(unlocked) {
}

VolcanoLevel::~VolcanoLevel() = default;

bool VolcanoLevel::init() {
    return Level::init_scene(m_tile_vec, m_texture_map);
}
