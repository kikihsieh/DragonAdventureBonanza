#ifndef DAB_COLLISION_SYSTEM_HPP
#define DAB_COLLISION_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include <map>
#include <list>

class CollisionSystem {
public:
    enum Side {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    bool init(std::list<Entity> *entities, std::map<int, Tile*>* tiles);

    void update(float ms);

private:
    void tile_collisions(Entity& entity, float ms);

    bool collide_with_tile(Entity& e1, Tile &tile, float ms);
    bool collide_with_entities(Entity& e);

    Side detect_collision(Entity& e1, Entity &e2);

    void land(Entity& entity);
    void grounded(Entity& entity);
    void fall(Entity& entity);

    std::list<Entity>* m_entities;
    std::map<int, Tile*>* m_tiles;
    float padding = 0.1;
};

#endif //DAB_COLLISION_SYSTEM_HPP
