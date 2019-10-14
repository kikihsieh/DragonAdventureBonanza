#include <vector>
#include <map>
#include "tile_map.hpp"

TileMap::TileMap(Level* level) : m_level(level) {
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

            // tiles less than 0 is an enemy
            if (*col < 0) {
                // TODO: calculate world position of enemy
                m_level->init_enemy(*col, {(float) (col - row->begin()), (float) (row - map.begin())});
            } else {
                std::shared_ptr<Tile> tile = std::make_shared<Tile>();
                tile->set_texture(dict.at(*col));
                if (!tile->init()) {
                    fprintf(stderr, "Failed to initialize tile!");
                    return false;
                }
                tile->set_position(col - row->begin(), row - map.begin());
                m_tiles.emplace_back(tile);
            }
        }
    }
    return true;
}

void TileMap::draw(const mat3 &projection) {
    for (auto& tile : m_tiles) {
        tile->draw(projection);
    }
}
