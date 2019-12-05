#ifndef DAB_HEALTH_SYSTEM_HPP
#define DAB_HEALTH_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>
#include <ecs/entities/tile.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>


class HealthSystem {
public:
    ~HealthSystem();
    bool init(std::list<Entity> *entities, std::map<int, Tile*>* tiles);

    void update(float ms);

    void respawn_at_last_safe(Entity& entity);

    bool player_died();

private:
    void update_last_safe(Entity& entity);

    bool m_player_died;

    std::list<Entity>* m_entities;
    std::map<int, Tile*>* m_tiles;
    
    Mix_Chunk* m_damage;
};


#endif //DAB_HEALTH_SYSTEM_HPP
