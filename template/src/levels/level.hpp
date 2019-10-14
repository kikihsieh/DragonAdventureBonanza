#ifndef DAB_LEVEL_HPP
#define DAB_LEVEL_HPP

#include <common.hpp>
#include <vector>
#include <levels/tile.hpp>
#include <map>
#include "tile_map.hpp"

typedef std::map<int, const char*> TexturePathMapping;

class Level {

public:
    explicit Level(bool unlocked);
    ~Level();

    virtual bool init() = 0;
    virtual const char * get_bg_texture_path() = 0;

    virtual void destroy();
    virtual void update();
    virtual void draw(const mat3& projection);

    bool is_level() const {
        return true;
    }

    bool is_unlocked() const {
        return m_unlocked;
    }

    vec2 get_x_boundaries() const {
        return m_x_boundaries;
    }

    vec2 get_y_boundaries() const {
        return m_y_boundaries;
    }

    std::vector<std::shared_ptr<Tile>> get_tiles() const {
        return m_tile_map->get_tiles();
    }

protected:
    bool init_scene(MapVector map, TexturePathMapping mapping);

    TextureMapping m_texture_mapping;
    TileMap* m_tile_map;

    bool m_unlocked;

protected:

    vec2 m_x_boundaries{};
    vec2 m_y_boundaries{};

    // Game entities
    std::vector<std::shared_ptr<Entity>> m_enemies;
};

#endif //DAB_LEVEL_HPP
