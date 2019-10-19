#include "level.hpp"

#include <utility>
#include <ecs/entities/player.hpp>

Level::Level(bool unlocked) :
    m_unlocked(unlocked),
    m_tile_map(nullptr),
    m_x_boundaries{-200.f, 0},
    m_y_boundaries{0, 0},
    m_physics_system(new PhysicsSystem()) {
}

Level::~Level() = default;

/** destroys resources not needed when the scene is not active **/
void Level::destroy() {
    Scene::destroy();
    m_entities.clear();
    delete m_tile_map;
    delete m_physics_system;
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
    m_physics_system->update(elapsed_ms);
}
