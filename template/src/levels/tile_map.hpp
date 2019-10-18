#ifndef DAB_TILE_MAP_HPP
#define DAB_TILE_MAP_HPP

#include <common.hpp>
#include <ecs/entities/tile.hpp>
#include <ecs/entities/spider.hpp>
#include "level.hpp"
#include <memory>

class Level; // forward declaration

typedef std::map<int, Texture*> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap {
    static vec2 TILE_SIZE;

public:
    explicit TileMap(Level* level);
    ~TileMap();

    //https://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way
    static int hash(int x, int y) {
        return x >= y ? x * x + x + y : x + y * y;  // where x, y >= 0
    }

    bool init(MapVector map, TextureMapping mapping);

    vec2 get_map_dim() {
        return m_map_dim;
    }

    const std::map<int, Tile> &get_tiles() const {
        return m_tiles;
    }

private:
    std::map<int, Tile> m_tiles;

private:

    Level* m_level;
    vec2 m_map_dim;
};

#endif //DAB_TILE_MAP_HPP
