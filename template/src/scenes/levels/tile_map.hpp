#ifndef DAB_TILE_MAP_HPP
#define DAB_TILE_MAP_HPP

#include <cmath>

#include <ecs/entities/tile.hpp>
#include <ecs/entities/spider.hpp>
#include <ecs/entities/glob.hpp>
#include <ecs/entities/projectile.hpp>
#include <ecs/entities/bat.hpp>
#include "level.hpp"

class Level; // forward declaration

typedef std::map<int, std::shared_ptr<Texture>> TextureMapping;
typedef std::map<int, std::shared_ptr<Properties>> TilePropertyMapping;
typedef std::vector<std::vector<int>> MapVector;

const int P = 1000;
const int G = 2000;

class TileMap {
public:
    explicit TileMap(Level* level);
    ~TileMap() {
        for (auto const& tile : m_tiles) {
            tile.second->destroy();
            delete tile.second;
        }
        m_tiles.clear();
    }

    static vec2 tile_size;
    static vec2 tile_scale;
    static vec2 tile_screen_size;

    //https://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way
    static int hash(int x, int y) {
        return x >= y ? x * x + x + y : x + y * y;  // where x, y >= 0
    }

    static std::pair<int, int> get_left_top_tile_pos_from_coord(float x, float y, vec2 size);
    static std::pair<int, int> get_tile_pos_from_coord(float x_pos, float y_pos);

    static vec2 get_coord_from_tile_pos(int col, int row) {
        float x = col * tile_size.x * tile_scale.x + tile_screen_size.x*0.5f;
        float y = row * tile_size.y * tile_scale.y + tile_screen_size.y*0.5f;
        return {x, y};
    }

    bool init(MapVector map, TextureMapping mapping, TilePropertyMapping property_map);

    vec2 get_map_dim() {
        return m_map_dim;
    }

    std::map<int, Tile*>* get_tiles();

private:
    std::map<int, Tile*> m_tiles;

private:

    Level* m_level;
    vec2 m_map_dim{};
};

#endif //DAB_TILE_MAP_HPP
