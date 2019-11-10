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
    //flying_style = (rand()% 3);
    m_tiles = tiles;
    m_entities = entities;
    for (auto &entity : *m_entities){
        if (!entity.flyable) {
            continue;
        } else{
            entity.flyable->center_c = entity.position;
            entity.flyable->initial_pos1 = entity.position;
            entity.flyable->final_pos2 = {entity.position.x+100,entity.position.y};
            entity.flyable->mid_p ={entity.position.x+5,entity.position.y +100};
            entity.flyable->boundary_x0 = entity.position.x +200;
            entity.flyable->boundary_x1 = entity.position.x -200;

        }
    }
    
    return true;
}


void EnemyMotionSystem::update(float ms) {
    for (auto &entity : *m_entities){
        if (entity.enemyai){
            move(ms, entity);
        }
        else if (entity.flyable){
           
            if (entity.flyable->fly_mode ==1 ){
                if (entity.flyable->flag){
                    fly_forward1(entity.flyable->t,entity);
                    entity.flyable->t += (ms/1000);
                   
                   
                    
                } else {
                    fly_backward1(entity.flyable->t,entity);
                    entity.flyable->t+= (ms/1000);
                    
                    
                }
                if (entity.flyable->t >=1.f){
                    entity.flyable->t=0.f;
                    entity.flyable->flag = !entity.flyable->flag;
                }
                
                
            }
            
            else if (entity.flyable->fly_mode ==2){fly_wave(ms, entity);}
            else if (entity.flyable->fly_mode ==3){fly_in_circle(ms, entity);}
        
        }
        
        
    }
}

void EnemyMotionSystem::fly_in_circle(float ms, Entity& entity){
    entity.flyable->center_c.x += entity.flyable->velocity_c.x * (ms/1000.f);
    entity.flyable->center_c.y += entity.flyable->velocity_c.y *(ms/1000.f) ;
    entity.flyable->angle_c += entity.flyable->rotate_speed *(ms/1000.f);
    vec2 off = {sin( entity.flyable->angle_c)*entity.flyable->radius, cos( entity.flyable->angle_c)*entity.flyable->radius};
    entity.position.x = entity.flyable->center_c.x + off.x;
    entity.position.y = entity.flyable->center_c.y + off.y;
}
void EnemyMotionSystem::fly_wave(float ms, Entity& entity){
    entity.flyable->center_c.y += entity.flyable->velocity_c.y *(ms/1000.f) ;
    entity.flyable->angle_c += entity.flyable->rotate_speed *(ms/1000.f);
    float off =  cos( entity.flyable->angle_c)*entity.flyable->radius;
    entity.position.y = entity.flyable->center_c.y + off;
    
    if (entity.is_facing_forward){
        entity.position.x += entity.flyable->speed;
        if  (entity.position.x >=   entity.flyable->boundary_x0 ){
            entity.is_facing_forward = !entity.is_facing_forward;
        }
        
    } else {
        entity.position.x -= entity.flyable->speed;
        if (entity.position.x <= entity.flyable->boundary_x1){
            entity.is_facing_forward = !entity.is_facing_forward;
        }
    }
    
}


void EnemyMotionSystem::fly_forward1(float t, Entity& entity){

    //if (entity.is_facing_forward){
        if (entity.position.x < entity.flyable->final_pos2.x){
            entity.position.x = QuadraticBezierPts(t, entity.flyable->initial_pos1, entity.flyable->mid_p, entity.flyable->final_pos2).x;
            entity.position.y = QuadraticBezierPts(t, entity.flyable->initial_pos1, entity.flyable->mid_p, entity.flyable->final_pos2 ).y;
            //std::cout << entity.position.x << ", " << entity.position.y << std::endl;
        }
        /*if (entity.position.x >= entity.flyable->final_pos2.x){
            entity.is_facing_forward = !entity.is_facing_forward;
    
        }
    }*/
}

void EnemyMotionSystem::fly_backward1(float t, Entity& entity){
    //if (entity.is_facing_forward){
        if (entity.flyable->initial_pos1.x < entity.position.x){
            entity.position.x = QuadraticBezierPts(t, entity.flyable->final_pos2 ,  entity.flyable->mid_p, entity.flyable->initial_pos1).x;
            entity.position.y = QuadraticBezierPts(t, entity.flyable->final_pos2 ,  entity.flyable->mid_p, entity.flyable->initial_pos1).y;
            
       /* } else if (entity.position.x <= entity.flyable->initial_pos1.x){
            entity.is_facing_forward = !entity.is_facing_forward;
            
        }*/
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

void EnemyMotionSystem::update_entities(std::list<Entity>* entities) {
    m_entities = entities;
}
