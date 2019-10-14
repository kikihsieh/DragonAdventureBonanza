#ifndef DAB_TILE_MAP_HPP
#define DAB_TILE_MAP_HPP

#include <common.hpp>
#include <levels/tile.hpp>

typedef std::map<int, Texture*> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap {
public:
    TileMap();
    ~TileMap();

    bool init(MapVector map, TextureMapping mapping);
    void draw(const mat3 &projection);

private:
    std::vector<std::shared_ptr<Tile>> m_tiles;
};

#endif //DAB_TILE_MAP_HPP
