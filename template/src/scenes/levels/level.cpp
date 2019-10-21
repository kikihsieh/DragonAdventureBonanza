#include "level.hpp"

#include <utility>
#include <ecs/entities/player.hpp>
#include "common.hpp"

Level::Level(bool unlocked) :
    m_unlocked(unlocked),
    m_tile_map(nullptr),
    m_x_boundaries{-200.f, 0},
    m_y_boundaries{0, 0},
    m_enemy_motionsystem(new EnemyMotionSystem()),
    m_physics_system(new PhysicsSystem()) {
}

Level::~Level() {
    delete m_physics_system;
    delete m_enemy_motionsystem;
    destroy();
}

/** destroys resources not needed when the scene is not active **/
void Level::destroy() {
    Scene::destroy();
    delete m_tile_map;
    m_entities.clear();
}

bool Level::init_scene(MapVector map, TexturePathMapping mapping) {
    m_tile_map = new TileMap(this);
    for (auto & iter : mapping) {
        auto* texture = new Texture();
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
    
    m_x_boundaries.y = m_tile_map->get_map_dim().x;
    m_y_boundaries.y = m_tile_map->get_map_dim().y;
    init_player();
    m_physics_system->init(&m_entities, m_tile_map->get_tiles());
    m_enemy_motionsystem->init(&m_entities, m_tile_map->get_tiles());
    return Scene::init();
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

vec2 Level::get_player_position(){
    return m_player->position;
}

bool Level::is_forward(){
    return m_player->is_facing_forward;
}

void Level::update(float elapsed_ms) {
    printf("ms %d", elapsed_ms * 0.001);
    m_physics_system->update(elapsed_ms);
    m_enemy_motionsystem->update(elapsed_ms);
    int index = m_player->animatable->index;
    if (index == 4) {
        m_player->animatable->index = 0;
        index = 0;
    }
    m_player->drawable->texture = m_player->animatable->m_texture_mapping[index];
    m_player->animatable->index++;
    Scene::update(elapsed_ms);
}
