#include "level.hpp"

#include <utility>
#include <enemies/spider.hpp>
#include <iostream>

Level::Level(bool unlocked) :
    m_unlocked(unlocked),
    m_tile_map(nullptr),
    m_x_boundaries{-200.f, 0},
    m_y_boundaries{200.f, 0} {
}

Level::~Level() = default;

/** destroys resources not needed when the scene is not active **/
void Level::destroy() {
    m_enemies.clear();
    delete m_tile_map;
}

bool Level::init_scene(MapVector map, TexturePathMapping mapping) {
    m_tile_map = new TileMap(this);
    for (auto & iter : mapping) {
        auto* texture = new Texture();
        if (!texture->is_valid()) {
            if (!texture->load_from_file(iter.second)) {
                fprintf(stderr, "Failed to load tile texture!");
                return false;
            }
        }
        m_texture_mapping.insert(TextureMapping::value_type(iter.first, texture));
    }
    if (!m_tile_map->init(std::move(map), m_texture_mapping)) {
        fprintf(stderr, "Failed to initialize tile map!");
        return false;
    }
    m_x_boundaries.y = m_x_boundaries.x + m_tile_map->get_map_dim().x;
    m_y_boundaries.y = m_y_boundaries.x + m_tile_map->get_map_dim().y;
    return true;
}

bool Level::init_enemy(int type, vec2 initial_pos) {
    std::shared_ptr<Spider> spider = std::make_shared<Spider>();
    spider->texture = m_texture_mapping.at(type);
    if (spider->init()) {
        spider->set_init_position_and_max_xy(initial_pos);
        m_enemies.emplace_back(spider);
    }
    else {
        fprintf(stderr, "Failed to initialize spider");
        return false;
    }
    return true;
}

void Level::update(float elapsed_ms) {
    for (auto& enemy : m_enemies) {
        Spider* spider = (Spider*) enemy.get();
        spider->update(elapsed_ms);
    }
}

void Level::draw(const mat3 &projection) {
    m_tile_map->draw(projection);
    for (auto& enemy : m_enemies) {
        enemy.get()->draw(projection);
    }
}

std::vector<std::shared_ptr<Tile>> Level::get_tiles() const {
    return m_tile_map->get_tiles();
}
