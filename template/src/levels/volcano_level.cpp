#include "volcano_level.hpp"

VolcanoLevel::VolcanoLevel(bool unlocked) :
        Level(unlocked) {
}

VolcanoLevel::~VolcanoLevel() = default;

bool VolcanoLevel::init() {
    return Level::init_scene(m_tile_vec, m_texture_map, get_bg_texture_path());
}

bool VolcanoLevel::init_walking_enemy(int type, vec2 initial_pos) {
    return true;
}
