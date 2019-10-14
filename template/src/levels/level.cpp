#include "level.hpp"

#include <utility>

Level::Level(bool unlocked) :
    m_unlocked(unlocked),
    m_tile_map(nullptr){
    // TODO: Calculate these values based on number of tiles
    m_x_boundaries = {-200.f, 1000.f};
    m_y_boundaries = {200.f, 700.f};
}

Level::~Level() = default;

/** destroys resources not needed when the scene is not active **/
void Level::destroy() {
    m_enemies.clear();
    delete m_tile_map;
}

bool Level::init_scene(MapVector map, TexturePathMapping mapping) {
    m_tile_map = new TileMap();
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
    return m_tile_map->init(std::move(map), m_texture_mapping);
}

void Level::update() {
    // TODO: update enemies here
}

void Level::draw(const mat3 &projection) {
    m_tile_map->draw(projection);
    // TODO: draw enemies;
}
