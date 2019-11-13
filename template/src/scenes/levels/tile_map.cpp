#include <vector>
#include <map>
#include "tile_map.hpp"
#include <iostream>

vec2 TileMap::tile_size = {64, 64};
vec2 TileMap::tile_scale = {0.75f, 0.75f };
vec2 TileMap::tile_screen_size = {tile_size.x * tile_scale.x, tile_size.y * tile_scale.y};

TileMap::TileMap(Level* level) : m_level(level) {
}

TileMap::~TileMap() = default;

bool TileMap::init(MapVector map, TextureMapping dict, TilePropertyMapping property_map) {
    std::vector< std::vector<int> >::const_iterator row;
    std::vector<int>::const_iterator col;

    int longest_row = 0;
    int col_index = 0;
    int row_count = 0;
    
    for (row = map.begin(); row != map.end(); ++row) {
        int row_index = row - map.begin();
        col_index = 0;
        for (col = row->begin(); col != row->end(); ++col) {
            if (*col == 0) {
                col_index ++;
                continue;
            }
            if (*col < 0) {
                if (*col == -1) {
                    Spider s(dict.at(*col), get_coord_from_tile_pos(col_index, row_index));
                    m_level->m_entities.emplace_back(s);
                }
                if (*col == -2) {
                    Glob s(dict.at(*col), get_coord_from_tile_pos(col_index, row_index));
                    m_level->m_entities.emplace_back(s);
                }
                if (*col <= -3 && *col >= -5) {
                    int fly_mode = (-1 * *col) % 3 + 1;
                    Bat b(dict.at(*col), get_coord_from_tile_pos(col_index, row_index), fly_mode);
                    m_level->m_entities.emplace_back(b);
                }
                if (*col == -8){
                    // TODO: init heart(health 1) here
                }
            } else {
                Tile* tile = nullptr;
                if (property_map.find(*col) == property_map.end()) {
                    Tile t(dict.at(*col), get_coord_from_tile_pos(col_index, row_index), tile_scale, tile_size);
                    tile = &t;
                } else {
                    Tile t(dict.at(*col), get_coord_from_tile_pos(col_index, row_index), tile_scale, tile_size, property_map.at(*col));
                    tile = &t;
                }
                auto it = m_level->m_entities.emplace(m_level->m_entities.end(), *tile);
                m_tiles.insert(std::map<int, Tile*>::value_type(
                        TileMap::hash(col_index, row_index), (Tile*) &(*it)));
            }
            col_index ++;
        }
        longest_row = (row_index > longest_row) ? row_index : longest_row;
        row_count ++;
    }

    m_map_dim.x = col_index * tile_screen_size.x;
    m_map_dim.y = row_count * tile_screen_size.y;

    return true;
}

std::pair<int, int> TileMap::get_tile_pos_from_coord(float x, float y, vec2 size) {
    float x_pos = x - size.x*0.5f;
    float y_pos = y - size.y*0.5f;

    float x_tiles = x_pos / tile_screen_size.x;
    float y_tiles = y_pos / tile_screen_size.y;

    int col = floor(x_tiles);
    int row = floor(y_tiles);
    return {col, row};
}
