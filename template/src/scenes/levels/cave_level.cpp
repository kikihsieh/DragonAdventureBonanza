#include "cave_level.hpp"

CaveLevel::CaveLevel(bool unlocked) :
    Level(unlocked) {
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
    player.shooting = new Shooting();
    player.shooting->time = 1000;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    return true;
}

bool CaveLevel::init() {
    m_physics_system = new PhysicsSystem(true);
    m_shooting_system = new ShootingSystem();
    return Level::init();
}
