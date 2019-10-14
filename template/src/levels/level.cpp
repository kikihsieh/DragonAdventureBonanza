#include "level.hpp"

#include <utility>
#include <enemies/spider.hpp>

Level::Level(bool unlocked) :
    m_unlocked(unlocked),
    m_tile_map(nullptr){
    // TODO: Calculate these values based on number of tiles
    m_x_boundaries = {-200.f, 1000.f};
    m_y_boundaries = {200.f, 700.f};
}

Level::~Level() = default;

/** destroys resources not needed when the scene is not active **/
void Level::destroy() {
    m_enemies.clear();
    delete m_tile_map;
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
    return m_tile_map->init(std::move(map), m_texture_mapping);
}

bool Level::init_enemy(int type, vec2 initial_pos) {
    std::shared_ptr<Spider> spider = std::make_shared<Spider>();
    spider->texture = m_texture_mapping.at(type);
    if (spider->init()) {
        spider->set_init_position_and_max_xy(initial_pos);
        m_enemies.emplace_back(spider);
    }
    else {
        fprintf(stderr, "Failed to initialize spider");
        return false;
    }
    return true;
}

void Level::update(float elapsed_ms) {
    for (auto& enemy : m_enemies) {
        Spider* spider = (Spider*) enemy.get();
        spider->update(elapsed_ms);
    }
}

void Level::draw(const mat3 &projection) {
    m_tile_map->draw(projection);
    for (auto& enemy : m_enemies) {
        enemy.get()->draw(projection);
    }
}

std::vector<std::shared_ptr<Tile>> Level::get_tiles() const {
    return std::vector<std::shared_ptr<Tile>>();
}
