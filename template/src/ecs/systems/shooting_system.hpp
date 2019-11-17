#ifndef DAB_SHOOTING_SYSTEM_HPP
#define DAB_SHOOTING_SYSTEM_HPP

#include "../entities/entity.hpp"
#include <ecs/entities/projectile.hpp>
#include <common.hpp>
#include <map>
#include <list>
#include <map>
#include <memory>
#include <random>

typedef std::map<int, const char*> TexturePathMapping;
typedef std::map<int, std::shared_ptr<Texture>> TextureMapping;

class ShootingSystem {
public:
    bool init(std::list<Entity> *entities, TextureMapping mapping, Entity *player, vec2 bounds);
    
    void update(float ms);
    
    bool initEntity(Entity& entity);
    void destroyEntity(Entity& entity);
    
private:
    std::list<Entity>* m_entities;
    std::list<Entity> m_projectiles;
    vec2 m_bounds;
    TextureMapping m_texture_mapping;
    Entity* m_player;
    
    std::default_random_engine m_rng;
    std::uniform_real_distribution<float> m_dist; // default 0..1
    
    bool load_from_file(Drawable::Effect& effect, const char* vs_path, const char* fs_path);
    void release(Drawable::Effect& effect);
    std::map<const char*, Drawable::Effect> m_effects;
};

#endif //DAB_SHOOTING_SYSTEM_HPP
