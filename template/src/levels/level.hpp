#ifndef DAB_LEVEL_HPP
#define DAB_LEVEL_HPP

#include <common.hpp>
#include <vector>
#include <tile.hpp>
#include <map>
#include "tile_map.hpp"

typedef std::map<int, const char*> TexturePathMapping;

class Level {

public:
    Level(const char* bg_texture_path, bool unlocked);
    ~Level();

    virtual bool init() = 0;
    virtual void update();
    virtual void draw(const mat3& projection);

    const char * get_bg_texture_path() const {
        return m_bg_texture_path;
    }

protected:
    bool init_textures(MapVector map, TexturePathMapping mapping);

    const char* m_bg_texture_path;

    TextureMapping m_texture_mapping;
    TileMap* m_tile_map;

    bool m_unlocked;

    vec2 m_x_boundaries;
    vec2 m_y_boundaries;

    // Game entities
    std::vector<Entity> m_enemies;
};

#endif //DAB_LEVEL_HPP
