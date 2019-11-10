#include "level.hpp"

#include <utility>
#include <ecs/entities/player.hpp>
#include "common.hpp"

Level::Level(bool unlocked) :
    m_unlocked(unlocked),
    m_tile_map(nullptr),
    m_collision_system(nullptr),
    m_physics_system(nullptr),
    m_airdash_system(nullptr),
    m_enemy_motion_system(nullptr),
    m_level_dim({0, 0}),
    m_shooting_system(nullptr){
}

bool Level::init() {
    m_collision_system = new CollisionSystem();
    m_physics_system = new PhysicsSystem();
    m_airdash_system = new AirDashSystem();
    m_enemy_motion_system = new EnemyMotionSystem();
    m_shooting_system = new ShootingSystem();
    init_level(get_map(), get_mapping());
    return Scene::init();
}

/** destroys resources not needed when the scene is not active **/
void Level::destroy() {
    Scene::destroy();
    delete m_physics_system;
    delete m_collision_system;
    delete m_airdash_system;
    delete m_tile_map;
    delete m_enemy_motion_system;
    delete m_shooting_system;

    m_physics_system = nullptr;
    m_collision_system = nullptr;
    m_airdash_system = nullptr;
    m_tile_map = nullptr;
    m_enemy_motion_system = nullptr;
    m_shooting_system = nullptr;
}

bool Level::init_level(MapVector map, TexturePathMapping mapping) {
    m_tile_map = new TileMap(this);
    for (auto & iter : mapping) {
        auto texture = std::make_shared<Texture>();
        if (!texture->is_valid()) {
            if (!texture->load_from_file(iter.second)) {
                fprintf(stderr, "Failed to load tile texture!");
                return false;
            }
        }
        m_texture_mapping.insert(TextureMapping::value_type(iter.first, texture));
    }
    if (!m_tile_map->init(std::move(map), m_texture_mapping)) {
        fprintf(stderr, "Failed to initialize tile map!");
        return false;
    }

    m_level_dim = m_tile_map->get_map_dim();

    return init_player() &&
            m_physics_system->init(&m_entities, m_tile_map->get_map_dim()) &&
            m_collision_system->init(&m_entities, m_tile_map->get_tiles()) &&
            m_airdash_system->init(&m_entities) && 
            m_enemy_motion_system->init(&m_entities, m_tile_map->get_tiles()) &&
            m_shooting_system->init(&m_entities, m_texture_mapping, m_player, m_level_dim) &&
            Scene::init();
}

bool Level::init_enemy(int type, vec2 initial_pos) {
    if (type == -1) {
        return init_walking_enemy(type, initial_pos);
    }

    return false;
}

bool Level::init_player(){
    Player player;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    return true;
}

void Level::update(float elapsed_ms) {
    m_airdash_system->update(elapsed_ms);
    m_physics_system->update(elapsed_ms);
    m_collision_system->update(elapsed_ms);
    m_enemy_motion_system->update(elapsed_ms);
    m_shooting_system->update(elapsed_ms);
    int index = m_player->animatable->index;
    m_player->drawable->texture = m_player->animatable->m_texture_mapping[index];
    Scene::update(elapsed_ms);
}
