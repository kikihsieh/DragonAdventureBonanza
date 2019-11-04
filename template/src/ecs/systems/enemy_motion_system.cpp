#include "enemy_motion_system.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>


bool EnemyMotionSystem::init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles) {
    //srand( time(0));
    //int max_waitTime = 10;
    //int min_waitTime = 4;
    //float countDown = (rand()%(max_waitTime - min_waitTime + 1) + min_waitTime) *10;
    
    // pick 1 or 0
    int init_direction = (rand() > RAND_MAX/2) ? 1 : 0;
    m_tiles = tiles;
    m_entities = entities;
    for (auto &entity : *m_entities){
        if (entity.flyable){
            center_c = entity.position;
            //entity.flyable->flyable_enemy= true;
        }
    }
    
    return true;
}

void EnemyMotionSystem::update(float ms) {
    for (auto &entity : *m_entities){
        if (entity.enemyai){
            move(ms, entity);
        }
        if (entity.flyable){
            fly(ms, entity);
        }
    }
}


void EnemyMotionSystem::fly(float ms, Entity& entity){
    for (auto &entity : *m_entities){
        if ( !entity.flyable || !entity.enemyai){
            continue;
        }
        
        center_c.x += velocity_c.x * (ms/1000.f);
        center_c.y += velocity_c.y *(ms/1000.f) ;
        angle_c += rotate_speed *(ms/1000.f);
        vec2 off = {sin(angle_c)*radius, cos(angle_c)*radius};
        //angle_c += (clockwise ? rotate_speed : -rotate_speed) ;
        //float x = sin(angle_c)*radiusX;
        //float y = cos(angle_c)*radiusY;
        //vec2 xy = {x,y};
        //entity.position = {center_c.x + xy.x, center_c.y+ xy.y};
        entity.position.x = center_c.x + off.x;
        entity.position.y = center_c.y + off.y;
    }
    
}

/*void EnemyMotionSystem::fly(float ms, Entity& entity){
 for (auto &entity : *m_entities){
 if (!entity.enemyai){
 continue;
 }
 vec2 p0 ={entity.position.x-2,entity.position.y};
 vec2 p1={entity.position.x-1,entity.position.y-1};
 vec2 p2 = {entity.position.x+1,entity.position.y-1};
 vec2 p3 = {entity.position.x+2,entity.position.y};
 QuadraticBezierPts(ms, p0, p1, p2, p3);
 
 if (entity.position.x < p3.x && entity.position.y < p3.y && entity.is_facing_forward){
 //entity.is_facing_forward = true;
 entity.position.x += QuadraticBezierPts(ms, p0, p1, p2, p3).x;
 entity.position.y += QuadraticBezierPts(ms, p0, p1, p2, p3).y;
 } else if (entity.position.x == p3.x && entity.position.y == p3.y && entity.is_facing_forward){
 entity.is_facing_forward = !entity.is_facing_forward;
 
 }
 */
/*vec2 QuadraticBezierPts(float t, vec2 p0, vec2 p1, vec2 p2, vec2 p3){
 //return: (1-t)2 p0 + 2(1-t)tp1 + t2p2
 //            u            u       tt
 //            uu*p0 + 2*u*t*p1 + tt*p2
 //
 float u = 1.0f - t;
 float uu = u*u;
 float uuu = uu*u;
 float tt = t*t;
 float ttt = tt*t;
 
 vec2 p = {uu*p0.x, uu*p0.y};
 vec2 pp = {2*u*t*p1.x,2*u*t*p1.y};
 vec2 ppp = {tt*p2.x, tt*p2.y};
 return {p.x+pp.x+ppp.x,p.y+pp.y+ppp.y} ;(
 
 vec2 p = {(uuu*p0.x) + (3*uu*t *p1.x)+ (3*u*tt*p2.x)+ (ttt*p3.x), (uuu*p0.y) + (3*uu*t *p1.y)+ (3*u*tt*p2.y)+ (ttt*p3.y)};
 p.x = round(p.x);
 p.y = round(p.y);
 return p;
 
 
 }*/

void EnemyMotionSystem::move(float ms, Entity& entity){
    
    for (auto &entity : *m_entities){
        if (!entity.physics || !entity.collider || !entity.enemyai){
            continue;
        }
        
        float e_height = entity.drawable->texture->height * entity.scale.x;
        float e_width = entity.drawable->texture->width * entity.scale.y;
        
        std::pair<int, int> enemy_tile_pos = TileMap::get_tile_pos_from_coord(entity.position.x, entity.position.y, {e_width, e_height});
        std::pair<int, int> platform_tile_pos = {enemy_tile_pos.first, enemy_tile_pos.second + 1};
        
        if (entity.collider->left || entity.collider->right){
            entity.is_facing_forward = !(entity.is_facing_forward);
            entity.physics->velocity.x *= -1;
            continue;
        }
        if (entity.is_facing_forward && m_tiles.count(TileMap::hash(platform_tile_pos.first+1, platform_tile_pos.second)) == 0) {
            entity.is_facing_forward = !(entity.is_facing_forward);
            entity.physics->velocity.x *= -1;
        } else if (!entity.is_facing_forward && m_tiles.count(TileMap::hash(platform_tile_pos.first, platform_tile_pos.second)) == 0) {
            entity.is_facing_forward = !(entity.is_facing_forward);
            entity.physics->velocity.x *= -1;
        }
    }
    
    
}

