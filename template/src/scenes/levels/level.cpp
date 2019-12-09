#include "level.hpp"

#include <utility>
#include <ecs/entities/player.hpp>
#include <iostream>
#include <world.hpp>
#include "common.hpp"
#include "ecs/systems/default_physics_system.hpp"

Level::Level() :
        m_tile_map(nullptr),
        m_level_dim({0, 0}),
        m_collision_system(nullptr),
        m_physics_system(nullptr),
        m_airdash_system(nullptr),
        m_enemy_motion_system(nullptr),
        m_health_system(nullptr),
        m_camera_system(nullptr),
        m_shooting_system(nullptr),
        m_intro_modal(nullptr) {
}

bool Level::init() {
    m_collision_system = new CollisionSystem();
    m_shooting_system = new ShootingSystem();

    m_enemy_motion_system = new EnemyMotionSystem();
    m_health_system = new HealthSystem();

    m_camera_system = new CameraSystem();
    return init_player() && init_level(get_map(), get_mapping());
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
    delete m_camera_system;


    if (m_intro_modal)
        m_intro_modal->destroy();
    delete m_intro_modal;

    m_physics_system = nullptr;
    m_collision_system = nullptr;
    m_airdash_system = nullptr;
    m_tile_map = nullptr;
    m_enemy_motion_system = nullptr;
    m_shooting_system = nullptr;
    m_camera_system = nullptr;
    m_intro_modal = nullptr;
}

void Level::draw_loading(const mat3& projection) {
    if (m_rendersystem) {
        vec2 camera_center = m_camera_system->get_center();
        m_rendersystem->render_text("LOADING...", projection, {camera_center.x - 90.f, camera_center.y}, {1.0, 1.0, 1.0}, 2.f);
    }
}

bool Level::init_level(MapVector map, TexturePathMapping mapping) {
    Button home(textures_path("buttons/home.png"));
    home.m_button_callback = [this](){load_scene(MAIN_MENU);};
    home.scale = {0.5f, 0.5f};
    m_buttons.emplace_back(home);

    Button help_btn(textures_path("buttons/help.png"));
    help_btn.m_button_callback = [this](){drawHelp = !drawHelp; state = (state == RUNNING) ? PAUSED : RUNNING;};
    help_btn.scale = {0.5f, 0.5f};
    m_buttons.emplace_back(help_btn);

    m_tile_map = new TileMap(this);
    for (auto &iter : mapping) {
        auto texture = std::make_shared<Texture>();
        if (!texture->is_valid()) {
            if (!texture->load_from_file(iter.second)) {
                fprintf(stderr, "%s", iter.second);
                return false;
            }
        }
        m_texture_mapping.insert(TextureMapping::value_type(iter.first, texture));
    }

    if (!m_tile_map->init(std::move(map), m_texture_mapping, get_property_map())) {
        fprintf(stderr, "Failed to initialize tile map!");
        return false;
    }
    m_level_dim = m_tile_map->get_map_dim();

    if (m_airdash_system && !m_airdash_system->init(&m_entities)) {
        return false;
    }

    return m_physics_system->init(&m_entities, m_tile_map->get_map_dim()) &&
           m_shooting_system->init(&m_entities, m_texture_mapping, m_player, m_level_dim) &&
           m_collision_system->init(&m_entities, m_tile_map->get_tiles()) &&
           m_enemy_motion_system->init(&m_entities, m_tile_map->get_tiles()) &&
           m_health_system->init(&m_entities, m_tile_map->get_tiles()) &&
           Scene::init();
    
}

void Level::update(float elapsed_ms, vec2 screen_size) {
    if (state == LOADED) {
        state = RUNNING;
        m_camera_system->init(m_level_dim, screen_size, use_vertical_camera());

        // All the things we need on first paused frame
        m_screen_size = screen_size;
        update_clipped(m_camera_system->get_center(), screen_size);
        level_intro.position = m_camera_system->get_center();
        Button* home = &m_buttons.front();
        home->position = add(m_camera_system->get_center(),{screen_size.x/2 - home->texture_size.x*home->scale.x + 25.f, -(screen_size.y/2 - home->texture_size.x*home->scale.x + 25.f)});
        Button* help_btn = &m_buttons.back();
        help_btn->position = add(m_camera_system->get_center(),{screen_size.x/2 - help_btn->texture_size.x*help_btn->scale.x*2, -(screen_size.y/2 - help_btn->texture_size.x*help_btn->scale.x + 25.f)});
        return;
    }

    if (state == PAUSED || state == LOADING) {
        return;
    }

    // TODO: This is a hack to get rid of the initialization error. The problem should be improved once
    //      efficiency issues are addressed
    if (elapsed_ms > 100) {
        return;
    }

    if (!m_camera_system || !m_physics_system || !m_collision_system ||
            !m_enemy_motion_system || !m_shooting_system || !m_health_system)
        return;

    update_clipped(m_camera_system->get_center(), screen_size);

    if (m_airdash_system)
        m_airdash_system->update(elapsed_ms);

    m_physics_system->update(elapsed_ms);
    m_collision_system->update(elapsed_ms);
    m_enemy_motion_system->update(elapsed_ms);
    m_shooting_system->update(elapsed_ms);

    help.position = m_camera_system->get_center();
    level_intro.position = m_camera_system->get_center();

    Scene::update(elapsed_ms, screen_size);
    m_camera_system->update(elapsed_ms, (Player *) m_player, screen_size);
    Button* home = &m_buttons.front();
    home->position = add(m_camera_system->get_center(),{screen_size.x/2 - home->texture_size.x*home->scale.x + 25.f, -(screen_size.y/2 - home->texture_size.x*home->scale.x + 25.f)});
    Button* help_btn = &m_buttons.back();
    help_btn->position = add(m_camera_system->get_center(),{screen_size.x/2 - help_btn->texture_size.x*help_btn->scale.x*2, -(screen_size.y/2 - help_btn->texture_size.x*help_btn->scale.x + 25.f)});

    m_health_system->update(elapsed_ms);

    if (m_collision_system->is_goal_reached()) {
        m_scene_change_callback();
    }

    if (m_health_system->player_died()) {
        load_scene(get_scene());
    }
}

void Level::update_clipped(vec2 camera_center, vec2 screen_size) {
    for (auto &entity: m_entities) {
        if (entity.is_background || entity.player_tag) {
            continue;
        }
        entity.clipped = entity.position.x > camera_center.x + screen_size.x * 0.55f ||
                         entity.position.x < camera_center.x - screen_size.x * 0.55f ||
                         entity.position.y > camera_center.y + screen_size.y * 0.55f ||
                         entity.position.y < camera_center.y - screen_size.y * 0.55f ||
                ((entity.clipped && (entity.is_enemy_proj || entity.is_player_proj)));
    }

    for (auto &tile: *m_tile_map->get_tiles()) {
        tile.second->clipped = tile.second->position.x > camera_center.x + screen_size.x * 0.55f ||
                tile.second->position.x < camera_center.x - screen_size.x * 0.55f ||
                tile.second->position.y > camera_center.y + screen_size.y * 0.55f ||
                tile.second->position.y < camera_center.y - screen_size.y * 0.55f;
    }
}

std::map<int, Tile *>* Level::get_tiles() {
    return m_tile_map->get_tiles();
}

void Level::on_mouse(int key, int action, double xpos, double ypos) {
    double x = xpos + m_camera_system->get_center().x - m_screen_size.x/2;
    double y = ypos + m_camera_system->get_center().y - m_screen_size.y/2;
    m_inputsystem->on_mouse_update(key, action, x, y);
}

void Level::on_key(int key, int action) {
    if (state == LOADED) {
        return;
    }

    if ((key == GLFW_KEY_R && action == GLFW_PRESS)) {
        World::playSFX(World::KEY_PRESS);
    }

    if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
        load_scene(get_scene());
        return;
    }

    Scene::on_key(key, action);
}
