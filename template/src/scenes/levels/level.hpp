#ifndef DAB_LEVEL_HPP
#define DAB_LEVEL_HPP

#include <common.hpp>
#include <vector>
#include <map>
#include <memory>
#include "../../ecs/systems/airdash_system.hpp"
#include "../../ecs/systems/health_system.hpp"
#include "../../ecs/systems/shooting_system.hpp"
#include "../../ecs/systems/physics_system.hpp"
#include "../../ecs/systems/collision_system.hpp"
#include "../../ecs/systems/enemy_motion_system.hpp"
#include "../../ecs/systems/camera_system.hpp"
#include "../../ecs/entities/tile.hpp"
#include "tile_map.hpp"
#include "scenes/scene.hpp"

typedef std::map<int, const char*> TexturePathMapping;
typedef std::map<int, std::shared_ptr<Properties>> TilePropertyMapping;
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
    void update(float elapsed_ms, vec2 screen_size) override;

    bool init_enemy(int type, vec2 initial_pos);
    bool init_player();

    virtual bool use_vertical_camera() {
        return false;
    }

    virtual std::map<int, Tile*>* get_tiles() override;

    bool is_level() override {
        return true;
    }

    bool is_unlocked() const {
        return m_unlocked;
    }

    float get_translation_x(vec2 screen_size) override {
        return m_camera_system->compute_translation_x(screen_size);
    }

    float get_translation_y(vec2 screen_size) override {
        return m_camera_system->compute_translation_y(screen_size);
    }

    Player* get_player() const {
        return (Player*) m_player;
    }

protected:
    virtual bool init_walking_enemy(int type, vec2 initial_pos) = 0;

    bool init_level(MapVector map, TexturePathMapping mapping);
    void update_clipped(vec2 camera_center, vec2 screen_size);

    TileMap* m_tile_map;
    TextureMapping m_texture_mapping;

    PhysicsSystem* m_physics_system;
    CollisionSystem* m_collision_system;
    EnemyMotionSystem* m_enemy_motion_system;
    AirDashSystem* m_airdash_system;
    HealthSystem* m_health_system;
    ShootingSystem* m_shooting_system;
    CameraSystem* m_camera_system;
    Entity* m_player;

    bool m_unlocked;
    vec2 m_level_dim;

private:
    virtual const MapVector get_map() const = 0;
    virtual const TexturePathMapping get_mapping() const = 0;
    virtual const TilePropertyMapping get_property_map() const = 0;
};

#endif //DAB_LEVEL_HPP
