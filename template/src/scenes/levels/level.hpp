#ifndef DAB_LEVEL_HPP
#define DAB_LEVEL_HPP

#include <common.hpp>
#include <vector>
#include <map>
#include <memory>
#include "../../ecs/systems/airdash_system.hpp"

#include "../../ecs/systems/physics_system.hpp"
#include "../../ecs/systems/collision_system.hpp"
#include "../../ecs/systems/enemy_motion_system.hpp"
#include "../../ecs/entities/tile.hpp"
#include "tile_map.hpp"
#include "scenes/scene.hpp"

typedef std::map<int, const char*> TexturePathMapping;
typedef std::map<int, std::shared_ptr<Texture>> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap; // forward declaration

class Level : public Scene
{

public:
    explicit Level(bool unlocked);
    virtual ~Level() = default;

    virtual bool init() override;

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

    vec2 get_player_position() override;
    bool is_forward() override;
protected:
    virtual bool init_walking_enemy(int type, vec2 initial_pos) = 0;

    bool init_level(MapVector map, TexturePathMapping mapping);

    TextureMapping m_texture_mapping;
    TileMap* m_tile_map;
    PhysicsSystem* m_physics_system;
    CollisionSystem* m_collision_system;
    EnemyMotionSystem* m_enemy_motionsystem;
    AirDashSystem* m_airdash_system;
    Entity* m_player;

    bool m_unlocked;

    vec2 m_x_boundaries;
    vec2 m_y_boundaries;

private:
    virtual MapVector get_map() = 0;
    virtual TexturePathMapping get_mapping() = 0;
};

#endif //DAB_LEVEL_HPP
