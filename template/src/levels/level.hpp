#ifndef DAB_LEVEL_HPP
#define DAB_LEVEL_HPP

#include <common.hpp>
#include <vector>
#include <map>
#include <memory>

#include "../ecs/systems/physics_system.hpp"
#include "../ecs/entities/entity.hpp"
#include "ecs/entities/tile.hpp"
#include "tile_map.hpp"
#include "scene.hpp"


typedef std::map<int, const char*> TexturePathMapping;
typedef std::map<int, Texture*> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap; // forward declaration

class Level : public Scene
{

public:
    explicit Level(bool unlocked);
    ~Level();

    virtual bool init() = 0;

    void destroy() override;
    void update(float elapsed_ms) override;

    bool init_enemy(int type, vec2 initial_pos);
    bool init_player();

    bool is_level() override {
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

protected:
    virtual bool init_walking_enemy(int type, vec2 initial_pos) = 0;

    bool init_scene(MapVector map, TexturePathMapping mapping);

    TextureMapping m_texture_mapping;
    TileMap* m_tile_map;
    PhysicsSystem* m_physics_system;

    bool m_unlocked;

    vec2 m_x_boundaries;
    vec2 m_y_boundaries;
};

#endif //DAB_LEVEL_HPP
