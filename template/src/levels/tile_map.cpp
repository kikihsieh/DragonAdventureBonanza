#include <utility>
#include <vector>
#include <map>
#include "tile_map.hpp"

void TileMap::init(MapVector map, TextureMapping dict) {
    std::vector< std::vector<int> >::const_iterator row;
    std::vector<int>::const_iterator col;

    for (row = map.begin(); row != map.end(); ++row) {
        for (col = row->begin(); col != row->end(); ++col) {
            if (*col == 0) {
                continue;
            }
            // TODO: enemies need to be treated differently here
            //      I think it would make sense to have the mapping
            //      of tiles use numbers 0-100, and enemies to go from 200-300
            //      so that it is easy to handle the two distinct cases here
            Tile* tile = new Tile();
            tile->set_texture(dict.at(*col));
            if (tile->init()) {
                tile->set_position(col - row->begin(), row - map.begin());
                m_tiles.emplace_back(tile);
            }
        }
    }
}

void TileMap::draw(const mat3 &projection) {
    for (auto& tile : m_tiles) {
        tile->draw(projection);
    }
}
