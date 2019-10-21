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
    
    /*for (auto &entity : *m_entities){
        if (!entity.enemyai){
            continue;
        }
        if (init_direction == 1){
            entity.is_facing_forward = false; // walk towards left
        } else {
            entity.is_facing_forward = false;
            
        }
    }*/
    
    return true;
}

void EnemyMotionSystem::update(float ms) {
    for (auto &entity : *m_entities){
        if (!entity.physics || !entity.collider || !entity.enemyai){
            continue;
        }
        
        if (entity.is_facing_forward){
            entity.physics->velocity.x = entity.physics->walk_speed;
        } else {
            entity.physics->velocity.x = -1* entity.physics->walk_speed;
        }

        
        float e_height = entity.drawable->texture->height * entity.scale.x;
        float e_width = entity.drawable->texture->width * entity.scale.y;
        
        std::pair<int, int> enemy_tile_pos = TileMap::get_tile_pos_from_coord(entity.position.x, entity.position.y, {e_width, e_height});
        
        std::pair<int, int> platform_tile_pos = {enemy_tile_pos.first, enemy_tile_pos.second + 1};
        
        if (entity.is_facing_forward && m_tiles.count(TileMap::hash(platform_tile_pos.first+1, platform_tile_pos.second)) == 0) {
            entity.is_facing_forward = !(entity.is_facing_forward);
            // change direction
               entity.physics->velocity.x *= -1;
        }
        else if (!entity.is_facing_forward && m_tiles.count(TileMap::hash(platform_tile_pos.first, platform_tile_pos.second)) == 0) {
            entity.is_facing_forward = !(entity.is_facing_forward);
            // change direction
            entity.physics->velocity.x *= -1;
        }
        if (entity.collider->left || entity.collider->right){
            entity.is_facing_forward = !(entity.is_facing_forward);
            // change direction 
            entity.physics->velocity.x *= -1;
        }
    }
    
}
