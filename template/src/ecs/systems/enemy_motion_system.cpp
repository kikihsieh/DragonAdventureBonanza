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
        if (!entity.enemyai){
            continue;
        }
        if (init_direction == 1){
            entity.is_facing_forward = false; // walk towards left
        } else {
            entity.is_facing_forward = false;
            
        }
    }
    
    return true;
}

void EnemyMotionSystem::update(float ms) {
    for (auto &entity : *m_entities){
        if (!entity.physics || !entity.collider || !entity.enemyai){
            continue;
        }
        //vec2 old_position = entity.position;
        if (entity.collider->left || entity.collider->right){
            //entity.position.x = old_position.x;
            entity.is_facing_forward = !(entity.is_facing_forward);
            // change direction 
            entity.physics->velocity.x = -1 * entity.physics->walk_speed;
        }
    }
    
}











