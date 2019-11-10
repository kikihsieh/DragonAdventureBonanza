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

    bool init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles);

    void update(float ms);
    void update_entities(std::list<Entity>* entities);

private:
    void tile_collisions(Entity& entity);
    void player_enemy_collision(Entity& entity);

    bool collide_with_tile(Entity& e1, Tile &tile);

    void player_projectile_collision(Entity& player);
    void enemy_projectile_collision(Entity& enemy);

    Side detect_collision(Entity& e1, Entity &e2);
    void collider_reset();

    void land(Entity& entity);
    void fall(Entity& entity);

    std::list<Entity>* m_entities;
    std::map<int, Tile*> m_tiles;
    float padding = 0.1;
};

#endif //DAB_COLLISION_SYSTEM_HPP
