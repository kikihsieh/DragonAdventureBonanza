#ifndef DAB_TILE_MAP_HPP
#define DAB_TILE_MAP_HPP

#include <common.hpp>
#include <levels/tile.hpp>
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
    void draw(const mat3 &projection);

    vec2 get_map_dim() {
        return m_map_dim;
    }

private:
    std::map<int, std::shared_ptr<Tile>> m_tiles;

    Level* m_level;
    vec2 m_map_dim;
};

#endif //DAB_TILE_MAP_HPP
