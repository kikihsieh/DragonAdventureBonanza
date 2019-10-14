#ifndef DAB_TILE_MAP_HPP
#define DAB_TILE_MAP_HPP

#include <common.hpp>
#include <tile.hpp>

typedef std::map<int, Texture*> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap {
public:
    void init(MapVector map, TextureMapping mapping);
    void draw(const mat3 &projection);

private:
    std::vector<Tile*> m_tiles;
};

#endif //DAB_TILE_MAP_HPP
