#ifndef DAB_LEVEL_HPP
#define DAB_LEVEL_HPP

#include <common.hpp>
#include <vector>
#include <map>
#include <memory>

#include "tile_map.hpp"
#include "tile.hpp"
#include "enemies/enemy.hpp"

typedef std::map<int, const char*> TexturePathMapping;
typedef std::map<int, Texture*> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap; // forward declaration

class Level {

public:
    explicit Level(bool unlocked);
    ~Level();

    virtual bool init() = 0;
    virtual const char * get_bg_texture_path() = 0;

    virtual void destroy();
    virtual void update(float elapsed_ms);
    virtual void draw(const mat3& projection);

    bool init_enemy(int type, vec2 initial_pos);

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

    std::vector<std::shared_ptr<Tile>> get_tiles() const;

protected:
    virtual bool init_walking_enemy(int type, vec2 initial_pos) = 0;

    bool init_scene(MapVector map, TexturePathMapping mapping);

    TextureMapping m_texture_mapping;
    TileMap* m_tile_map;

    bool m_unlocked;

    vec2 m_x_boundaries{};
    vec2 m_y_boundaries{};

    // Game entities
    std::vector<std::shared_ptr<Enemy>> m_enemies;
};

#endif //DAB_LEVEL_HPP
