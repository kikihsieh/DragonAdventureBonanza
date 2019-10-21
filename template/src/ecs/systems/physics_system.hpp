#ifndef DAB_PHYSICS_SYSTEM_HPP
#define DAB_PHYSICS_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include <map>
#include <list>

class PhysicsSystem {
public:
    bool init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles, vec2 level_bounds);

    void update(float ms);

private:
    void tile_collisions(Entity& entity);
    void entity_collisions(Entity& entity);
    void collide(Entity& e1, Entity& e2);
    void move(float ms, Entity& entity);

    std::list<Entity>* m_entities;
    std::map<int, Tile*> m_tiles;

    vec2 m_level_bounds_x;
    vec2 m_level_bounds_y;
};

#endif //DAB_PHYSICS_SYSTEM_HPP
