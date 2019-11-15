#ifndef DAB_ENEMY_MOTION_SYSTEM_HPP
#define DAB_ENEMY_MOTION_SYSTEM_HPP

#include <ecs/entities/tile.hpp>
#include "../entities/entity.hpp"
#include <map>
#include <list>

class EnemyMotionSystem {
public:
    bool init(std::list<Entity> *entities, std::map<int, Tile*>* tiles);
    vec2 QuadraticBezierPts(float t, vec2 p0, vec2 p1, vec2 p2);

    void update(float ms);
     float t;
    /*vec2 velocity_c = {1,0};
    float rotate_speed = 3.f;
    float radius = 50.f;
   
    bool flag= true;
    int speed;
    int flying_style;*/
    
private:
    //void tile_collisions(Entity& entity);
    //void entity_collisions(Entity& entity);
    //void collide_with_tile(Entity& e1, Entity& e2);
    void move(float ms, Entity& entity);
    void fly_in_circle(float ms, Entity& entity);
    void fly_wave(float ms, Entity& entity);
    void fly_forward1(float ms, Entity& entity);
    void fly_backward1(float ms, Entity& entity);
    

    std::list<Entity>* m_entities;
    std::map<int, Tile*>* m_tiles;
  
};

#endif //DAB_ENEMY_MOTION_SYSTEM_HPP
