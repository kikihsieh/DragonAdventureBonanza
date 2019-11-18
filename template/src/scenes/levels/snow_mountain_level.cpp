#include "snow_mountain_level.hpp"

SnowMountainLeve::SnowMountainLeve(bool unlocked) :
        Level(unlocked) {
}

void SnowMountainLeve::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    s.drawable->texture->height = 50;
    s.physics->walk_speed = 85;
    s.physics->velocity.x = s.physics->walk_speed;
    m_entities.emplace_back(s);
}

void SnowMountainLeve::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    g.shooting->time = 6000;
    g.drawable->texture->height = 320;
    g.drawable->texture->width = 250;
    m_entities.emplace_back(g);
}
