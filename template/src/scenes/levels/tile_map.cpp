#include <vector>
#include <map>
#include "tile_map.hpp"

vec2 TileMap::tile_size = {64, 64};
vec2 TileMap::tile_scale = {0.75f, 0.75f };
vec2 TileMap::tile_screen_size = {tile_size.x * tile_scale.x, tile_size.y * tile_scale.y};

TileMap::TileMap(Level* level) : m_level(level) {
}

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
            if (*col == P) {
                m_level->get_player()->position = get_coord_from_tile_pos(col_index, row_index);
            } else if (*col == G) {
                Tile* tile = new Tile(get_coord_from_tile_pos(col_index, row_index), tile_scale, tile_size, std::make_shared<Properties>(Properties::GOAL));
                m_tiles.insert(std::map<int, Tile*>::value_type(
                        TileMap::hash(col_index, row_index), tile));
            } else if (*col < 0) {
                if (*col == -1) {
                    m_level->init_walking_enemy(dict.at(*col), get_coord_from_tile_pos(col_index, row_index));
                }
                if (*col == -2) {
                    m_level->init_throwing_enemy(dict.at(*col), get_coord_from_tile_pos(col_index, row_index));
                }
                if (*col <= -3 && *col >= -5) {
                    int fly_mode = (-1 * *col) % 3 + 1;
                    Bat b(dict.at(*col), get_coord_from_tile_pos(col_index, row_index), fly_mode);
                    m_level->m_entities.emplace_back(b);
                }
            } else {
                Tile* tile;
                if (property_map.find(*col) == property_map.end()) {
                    tile = new Tile(dict.at(*col), get_coord_from_tile_pos(col_index, row_index), tile_scale, tile_size);
                } else {
                    tile = new Tile(dict.at(*col), get_coord_from_tile_pos(col_index, row_index), tile_scale, tile_size, property_map.at(*col));
                    if (property_map.at(*col)->type == Properties::TORCH) {
                        tile->properties = std::make_shared<Properties>(Properties::Type::TORCH);
                        m_level->m_lights.emplace_back(tile);
                    } else if (property_map.at(*col)->type == Properties::TORCH_LIT) {
                        tile->animatable->num_columns = 4;
                        tile->drawable->texture->width *= tile->animatable->num_columns ;
                        tile->animatable->frame_index = {0,0};
                        tile->drawable->vs_shader = shader_path("animated.vs.glsl");
                        tile->drawable->fs_shader = shader_path("animated.fs.glsl");
                        
                        m_level->m_lights.emplace_back(tile);
                    }
                    else if (property_map.at(*col)->type == Properties::HEALTH){
                        tile->animatable->num_columns = 5;
                        tile->drawable->texture->width *= tile->animatable->num_columns ;
                        tile->animatable->frame_index = {0,0};
                        tile->drawable->vs_shader = shader_path("animated.vs.glsl");
                        tile->drawable->fs_shader = shader_path("animated.fs.glsl");
                     
                     }

                }
                m_tiles.insert(std::map<int, Tile*>::value_type(
                        TileMap::hash(col_index, row_index), tile));
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

std::pair<int, int> TileMap::get_left_top_tile_pos_from_coord(float x, float y, vec2 size) {
    float x_pos = x - size.x*0.5f;
    float y_pos = y - size.y*0.5f;

    float x_tiles = x_pos / tile_screen_size.x;
    float y_tiles = y_pos / tile_screen_size.y;

    int col = floor(x_tiles);
    int row = floor(y_tiles);
    return {col, row};
}

std::pair<int, int> TileMap::get_tile_pos_from_coord(float x_pos, float y_pos) {
    float x_tiles = x_pos / tile_screen_size.x;
    float y_tiles = y_pos / tile_screen_size.y;

    int col = floor(x_tiles);
    int row = floor(y_tiles);
    return {col, row};
}

std::map<int, Tile*>* TileMap::get_tiles() {
    return &m_tiles;
}
