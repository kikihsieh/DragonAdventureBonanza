#include <vector>
#include <map>
#include "tile_map.hpp"

vec2 TileMap::TILE_SIZE = {48, 48};

TileMap::TileMap(Level* level) : m_level(level) {
}

TileMap::~TileMap() {
    m_tiles.clear();
}

bool TileMap::init(MapVector map, TextureMapping dict) {
    std::vector< std::vector<int> >::const_iterator row;
    std::vector<int>::const_iterator col;

    int longest_row = 0;

    for (row = map.begin(); row != map.end(); ++row) {
        int row_index = row - map.begin();
        for (col = row->begin(); col != row->end(); ++col) {

            if (*col == 0) {
                continue;
            }

            int col_index = col - row->begin();

            // tiles less than 0 are entities
            if (*col < 0) {
                float pos_x = ((float) (col_index))  * TILE_SIZE.x;
                float pos_y = ((float) (row_index) * TILE_SIZE.y);
                m_level->init_enemy(*col, {pos_x, pos_y});
            } else {
                std::shared_ptr<Tile> tile = std::make_shared<Tile>();
                tile->set_texture(dict.at(*col));
                if (!tile->init()) {
                    fprintf(stderr, "Failed to initialize tile!");
                    return false;
                }
                tile->set_position(col - row->begin(), row - map.begin());
                m_tiles.insert(std::map<int, std::shared_ptr<Tile>>::value_type(
                        TileMap::hash(col_index, row_index), tile));
            }
        }
        longest_row = (row_index > longest_row) ? row_index : longest_row;
    }
    m_map_dim.x = ((float) longest_row) * TILE_SIZE.x;
    m_map_dim.y = ((float) (map.end() - map.begin())) * TILE_SIZE.y;
    return true;
}

void TileMap::draw(const mat3 &projection) {
    for (auto& tile : m_tiles) {
        tile.second->draw(projection);
    }
}
