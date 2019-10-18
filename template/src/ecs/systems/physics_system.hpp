#ifndef DAB_PHYSICS_SYSTEM_HPP
#define DAB_PHYSICS_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include <map>

class PhysicsSystem {
public:
    bool init(std::vector<Entity> *entities, std::map<int, Tile*> tiles);

    void update(float ms);

private:
    void tile_collisions(Entity& entity);
    void entity_collisions(Entity& entity);

    std::vector<Entity>* m_entities;
    std::map<int, Tile*> m_tiles;
};

#endif //DAB_PHYSICS_SYSTEM_HPP
