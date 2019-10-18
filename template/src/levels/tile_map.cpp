#include <vector>
#include <map>
#include "tile_map.hpp"

vec2 TileMap::TILE_SIZE = {64, 64};
vec2 TileMap::TILE_SCALE = { 0.75f, 0.75f };

TileMap::TileMap(Level* level) : m_level(level) {
}

TileMap::~TileMap() = default;

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

            if (*col < 0) {
                Spider s(dict.at(*col), get_coord_from_tile_pos(col_index, row_index));
                m_level->m_entities.emplace_back(s);
            } else {
                Tile tile(dict.at(*col), get_coord_from_tile_pos(col_index, row_index), TILE_SCALE, TILE_SIZE);
                auto it = m_level->m_entities.emplace(m_level->m_entities.end(), tile);
                m_tiles.insert(std::map<int, Tile*>::value_type(
                        TileMap::hash(col_index, row_index), (Tile*) &*it));
                }
        }
        longest_row = (row_index > longest_row) ? row_index : longest_row;
    }
    
    m_map_dim.x = ((float) longest_row) * TILE_SIZE.x;
    m_map_dim.y = ((float) (map.end() - map.begin())) * TILE_SIZE.y;
    return true;
}
