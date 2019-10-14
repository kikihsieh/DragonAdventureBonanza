#include "level.hpp"

#include <utility>

Level::Level(const char* bg_texture_path, bool unlocked) :
    m_bg_texture_path(bg_texture_path),
    m_unlocked(unlocked),
    m_tile_map(new TileMap()){
}

Level::~Level() {

}

bool Level::init_textures(MapVector map, TexturePathMapping mapping) {
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
    m_tile_map->init(std::move(map), m_texture_mapping);
    return true;
}

void Level::update() {
    // TODO: update enemies here
}

void Level::draw(const mat3 &projection) {
    m_tile_map->draw(projection);
    // TODO: draw enemies;
}
