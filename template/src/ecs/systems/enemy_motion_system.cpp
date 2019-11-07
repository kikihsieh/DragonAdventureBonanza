#include "enemy_motion_system.hpp"
#include "common.hpp"

#include <cmath>
#include <utility>
#include <scenes/levels/tile_map.hpp>
#include <iostream>


bool EnemyMotionSystem::init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles) {
    //srand( time(0));
    //int max_waitTime = 10;
    //int min_waitTime = 4;
    //float countDown = (rand()%(max_waitTime - min_waitTime + 1) + min_waitTime) *10;
    
    // pick 1 or 0
    //int init_direction = (rand() > RAND_MAX/2) ? 1 : 0;
    m_tiles = tiles;
    m_entities = entities;
    for (auto &entity : *m_entities){
        if (entity.flyable){
            center_c = entity.position;
            t =0.f;
            intial_pos1 = entity.position;
            final_pos2 = {entity.position.x+100,entity.position.y};
            mid_p ={entity.position.x+2,entity.position.y +100};
            
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
            //fly(ms, entity);
            if (flag){
                fly2(t,entity);
            t += (ms/1000);
            } else {
                fly3(t,entity);
                t+= (ms/1000);
            }
        }
        if (t >=1){
            t=0;
            flag = !flag;
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

void EnemyMotionSystem::fly2(float t, Entity& entity){
   /*if (t >=1){
        t=0;
        //entity.is_facing_forward = !entity.is_facing_forward;
    }*/
    if (entity.is_facing_forward){
        if (entity.position.x < final_pos2.x){
            entity.position.x = QuadraticBezierPts(t, intial_pos1, mid_p, final_pos2).x;
            entity.position.y = QuadraticBezierPts(t, intial_pos1, mid_p, final_pos2).y;
            //std::cout << entity.position.x << ", " << entity.position.y << std::endl;
        }
        if (entity.position.x >= final_pos2.x){
            entity.is_facing_forward = !entity.is_facing_forward;
            //std::cout << "face backward" << std::endl;
            //t=0;
        }
        
    }/*else {
       
        if (intial_pos1.x < entity.position.x){
            entity.position.x = QuadraticBezierPts(t, final_pos2, mid_p, intial_pos1).x;
            entity.position.y = QuadraticBezierPts(t, final_pos2, mid_p, intial_pos1).y;
            //std::cout << entity.position.x << ", " << entity.position.y << std::endl;
        } else if (entity.position.x <= intial_pos1.x){
            entity.is_facing_forward = !entity.is_facing_forward;
            //std::cout << "face forward" << std::endl;
            //t=0;
            
        }
    }
    //std::cout << t << std::endl;*/
}

void EnemyMotionSystem::fly3(float t, Entity& entity){
if (entity.is_facing_forward){
        if (intial_pos1.x < entity.position.x){
            entity.position.x = QuadraticBezierPts(t, final_pos2, mid_p, intial_pos1).x;
            entity.position.y = QuadraticBezierPts(t, final_pos2, mid_p, intial_pos1).y;
            //std::cout << entity.position.x << ", " << entity.position.y << std::endl;
        } else if (entity.position.x <= intial_pos1.x){
            entity.is_facing_forward = !entity.is_facing_forward;
            //std::cout << "face forward" << std::endl;
            //t=0;
            
        }
    
}
}

vec2 EnemyMotionSystem::QuadraticBezierPts( float t, vec2 p0, vec2 p1, vec2 p2){
 //return: (1-t)^2 p0 + 2(1-t)tp1 + t^2 p2
 //            u            u       tt
 //            uu*p0 + 2*u*t*p1 + tt*p2
 //
    float u = 1.0f - t;
    float uu = u*u;
    //float uuu = uu*u;
    float tt = t*t;
    //float ttt = tt*t;
    
  
    vec2 p = mul(p0,uu);
    vec2 pp = mul(p1,2*u*t );
    vec2 ppp = mul(p2,tt);
    return add(add(p,pp),ppp);
 
 }

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

