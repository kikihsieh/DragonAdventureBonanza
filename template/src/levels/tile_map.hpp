#ifndef DAB_TILE_MAP_HPP
#define DAB_TILE_MAP_HPP

#include <math.h>

#include <ecs/entities/tile.hpp>
#include <ecs/entities/spider.hpp>
#include "level.hpp"

class Level; // forward declaration

typedef std::map<int, Texture*> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap {
public:
    explicit TileMap(Level* level);
    ~TileMap();

    static vec2 TILE_SIZE;
    static  vec2 TILE_SCALE;

    //https://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way
    static int hash(int x, int y) {
        return x >= y ? x * x + x + y : x + y * y;  // where x, y >= 0
    }

    static std::pair<int, int> get_tile_pos_from_coord(int x, int y) {
        int col = floor((TILE_SIZE.x*0.5f*TILE_SCALE.x + x) / TILE_SIZE.x*TILE_SCALE.x);
        int row = floor((TILE_SIZE.y*0.5f*TILE_SCALE.y + y) / TILE_SIZE.y*TILE_SCALE.y);
        return {col, row};
    }

    static vec2 get_coord_from_tile_pos(int col, int row) {
        float x = col * TILE_SIZE.x*TILE_SCALE.x - TILE_SIZE.x*0.5f*TILE_SCALE.x;
        float y = row * TILE_SIZE.y*TILE_SCALE.y + TILE_SIZE.y*0.5f*TILE_SCALE.y;
        return {x, y};
    }

    bool init(MapVector map, TextureMapping mapping);

    vec2 get_map_dim() {
        return m_map_dim;
    }

    const std::map<int, Tile*> &get_tiles() const {
        return m_tiles;
    }

private:
    std::map<int, Tile*> m_tiles;

private:
    Level* m_level;
    vec2 m_map_dim;
};

#endif //DAB_TILE_MAP_HPP
