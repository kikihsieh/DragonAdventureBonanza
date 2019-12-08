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

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

typedef std::map<int, const char*> TexturePathMapping;
typedef std::map<int, std::shared_ptr<Properties>> TilePropertyMapping;
typedef std::map<int, std::shared_ptr<Texture>> TextureMapping;
typedef std::vector<std::vector<int>> MapVector;

class TileMap; // forward declaration

class Level : public Scene
{

public:
    explicit Level();
    virtual ~Level() = default;

    virtual bool init() override;

    void destroy() override;
    virtual void update(float elapsed_ms, vec2 screen_size) override;

    virtual bool init_player() = 0;

    virtual bool use_vertical_camera() {
        return false;
    }

    Modal get_level_intro() override {
        return *m_intro_modal;
    }

    void draw_loading(const mat3& projection) override;

    virtual std::map<int, Tile*>* get_tiles() override;

    virtual void init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {};
    virtual void init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {};
    virtual Scene_name get_scene() = 0;
    
    bool is_level() override {
        return true;
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
    void on_mouse(int key, int action, double xpos, double ypos) override;
    void on_key(int key, int action) override;
    bool should_draw_level_intro() override { return true; }

protected:
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
    Modal* m_intro_modal;

    vec2 m_level_dim;

private:
    virtual const MapVector get_map() const = 0;
    virtual const TexturePathMapping get_mapping() const = 0;
    virtual const TilePropertyMapping get_property_map() const = 0;
};

#endif //DAB_LEVEL_HPP
