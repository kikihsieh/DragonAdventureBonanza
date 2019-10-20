#ifndef DAB_PHYSICS_SYSTEM_HPP
#define DAB_PHYSICS_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include <map>
#include <list>

class PhysicsSystem {
public:
    bool init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles);

    void update(float ms);

private:
    void tile_collisions(Entity& entity, vec2 old_pos);
    void entity_collisions(Entity& entity);
    void collide(Entity& e1, Entity& e2, vec2 old_pos);
    void move(float ms, Entity& entity);

    std::list<Entity>* m_entities;
    std::map<int, Tile*> m_tiles;
};

#endif //DAB_PHYSICS_SYSTEM_HPP
