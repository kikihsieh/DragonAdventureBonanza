#include <ecs/entities/spider.hpp>
#include "forest_level.hpp"

ForestLevel::ForestLevel(bool unlocked) :
    Level(unlocked) {
}

void ForestLevel::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    m_entities.emplace_back(s);
}

void ForestLevel::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    m_entities.emplace_back(g);
}

