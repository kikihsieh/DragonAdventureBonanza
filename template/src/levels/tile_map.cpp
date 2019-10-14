#include <vector>
#include <map>
#include "tile_map.hpp"

TileMap::TileMap(Level* level) : m_level(level), m_tile_size() {
}

TileMap::~TileMap() {
    m_tiles.clear();
}

bool TileMap::init(MapVector map, TextureMapping dict) {
    std::vector< std::vector<int> >::const_iterator row;
    std::vector<int>::const_iterator col;

    for (row = map.begin(); row != map.end(); ++row) {
        for (col = row->begin(); col != row->end(); ++col) {
            if (*col == 0) {
                continue;
            }

            // tiles less than 0 are enemies
            if (*col < 0) {
                float pos_x = ((float) (col - row->begin()) * m_tile_size.x);
                float pos_y = ((float) (row - map.begin()) * m_tile_size.y);
                m_level->init_enemy(*col, {pos_x, pos_y});
            } else {
                std::shared_ptr<Tile> tile = std::make_shared<Tile>();
                tile->set_texture(dict.at(*col));
                if (!tile->init()) {
                    fprintf(stderr, "Failed to initialize tile!");
                    return false;
                }
                tile->set_position(col - row->begin(), row - map.begin());
                m_tiles.emplace_back(tile);
                // TODO: Tile size should be set by tile map or at least initialized better
                //  because currently it could be 0 if the first tile it encounters is an enemy
                if (m_tile_size.x == 0 && m_tile_size.y == 0) {
                    m_tile_size = tile->get_size();
                }
            }
        }
    }
    // TODO: get from number of rows and columns
    m_map_dim.x = 50.f * m_tile_size.x;
    m_map_dim.y = 17.f * m_tile_size.y;
    return true;
}

void TileMap::draw(const mat3 &projection) {
    for (auto& tile : m_tiles) {
        tile->draw(projection);
    }
}
