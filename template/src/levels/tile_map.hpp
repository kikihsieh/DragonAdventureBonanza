#ifndef DAB_TILE_MAP_HPP
#define DAB_TILE_MAP_HPP

#include <common.hpp>
#include <levels/tile.hpp>
#include "level.hpp"

class Level; // forward declaration

typedef std::map<int, Texture*> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap {
public:
    explicit TileMap(Level* level);
    ~TileMap();

    bool init(MapVector map, TextureMapping mapping);
    void draw(const mat3 &projection);

    std::vector<std::shared_ptr<Tile>> get_tiles() const {
        return m_tiles;
    }

private:
    std::vector<std::shared_ptr<Tile>> m_tiles;
    Level* m_level;
};

#endif //DAB_TILE_MAP_HPP
