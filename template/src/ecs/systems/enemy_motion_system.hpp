#ifndef DAB_ENEMY_MOTION_SYSTEM_HPP
#define DAB_ENEMY_MOTION_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include "../entities/entity.hpp"
#include <map>
#include <list>

class EnemyMotionSystem {
public:
    bool init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles);
    vec2 QuadraticBezierPts(float t, vec2 p0, vec2 p1, vec2 p2);

    void update(float ms);
    
    vec2 velocity_c = {1,0};
    float rotate_speed = 3.f;
    float radius = 50.f;
    float t;
    bool flag= true;
    vec2 intial_pos1;
    vec2 final_pos2;
    vec2 mid_p;
private:
    //void tile_collisions(Entity& entity);
    //void entity_collisions(Entity& entity);
    //void collide(Entity& e1, Entity& e2);
    void move(float ms, Entity& entity);
    void fly(float ms, Entity& entity);
    void fly2(float ms, Entity& entity);
    void fly3(float ms, Entity& entity);
    

    std::list<Entity>* m_entities;
    std::map<int, Tile*> m_tiles;
    
    vec2 center_c;
    float angle_c;
    
};

#endif //DAB_ENEMY_MOTION_SYSTEM_HPP
