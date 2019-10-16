#include <ecs/entities/spider.hpp>
#include "forest_level.hpp"

ForestLevel::ForestLevel(bool unlocked) :
    Level(unlocked) {
}

ForestLevel::~ForestLevel() = default;

bool ForestLevel::init() {
    return Level::init_scene(m_tile_vec, m_texture_map, get_bg_texture_path());
}

bool ForestLevel::init_walking_enemy(int type, vec2 initial_pos) {
    std::shared_ptr<Spider> spider = std::make_shared<Spider>();
    spider->texture = m_texture_mapping.at(type);
    if (spider->init()) {
        spider->set_init_position_and_max_xy(initial_pos);
        m_entities.emplace_back(spider);
    }
    else {
        fprintf(stderr, "Failed to initialize spider");
        return false;
    }
    return true;
}
