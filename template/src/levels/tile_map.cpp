#include <vector>
#include <map>
#include "tile_map.hpp"

TileMap::TileMap() {

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
            // TODO: enemies need to be treated differently here
            //      I think it would make sense to have the mapping
            //      of tiles use numbers, and enemies to use letters like
            //      w for walking enemy, f for flying etc. etc.
            //      so that it is easy to handle the two distinct cases here
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
    return true;
}

void TileMap::draw(const mat3 &projection) {
    for (auto& tile : m_tiles) {
        tile.get()->draw(projection);
    }
}
