#ifndef DAB_ENEMY_MOTION_SYSTEM_HPP
#define DAB_ENEMY_MOTION_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include "../entities/entity.hpp"
#include <map>
#include <list>

class EnemyMotionSystem {
public:
    bool init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles);

    void update(float ms);
    
    
    vec2 velocity_c = {1,0};
    float rotate_speed = 1.f;
    float radius = 1.f;

private:
    //void tile_collisions(Entity& entity);
    //void entity_collisions(Entity& entity);
    //void collide_with_tile(Entity& e1, Entity& e2);
    void move(float ms, Entity& entity);
    void fly(float ms, Entity& entity);

    std::list<Entity>* m_entities;
    std::map<int, Tile*> m_tiles;
    
    vec2 center_c;
    float angle_c;
    
};

#endif //DAB_ENEMY_MOTION_SYSTEM_HPP
