#include "cave_level.hpp"

CaveLevel::CaveLevel() :
    Level() {
}

void CaveLevel::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    m_entities.emplace_back(s);
}

void CaveLevel::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    m_entities.emplace_back(g);
}

bool CaveLevel::init_player() {
    Player player;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    return true;
}

bool CaveLevel::init() {
    m_physics_system = new PhysicsSystem(true);
    Entity dark = Entity();
    dark.drawable = new Drawable();
    dark.is_background = true;
    dark.clipped = false;
    dark.drawLast = true;
    dark.drawable->texture_path = textures_path("cave/background.png");
    dark.drawable->fs_shader = shader_path("cave.fs.glsl");
    dark.drawable->vs_shader = shader_path("cave.vs.glsl");
    m_entities.emplace_back(dark);
    bool result = Level::init();
    Entity sec = *std::next(m_entities.begin());
    m_entities.erase(std::next(m_entities.begin()));
    m_entities.emplace_back(sec);
    return result;
}
