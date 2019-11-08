#ifndef DAB_HEALTH_SYSTEM_HPP
#define DAB_HEALTH_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>
#include <ecs/entities/tile.hpp>

class HealthSystem {
public:
    bool init(std::list<Entity> *entities, const std::map<int, Tile*>& tiles);

    void update(float ms);

    void respawn_at_last_safe(Entity& entity);

    bool entities_changed();
    bool player_died();

    std::list<Entity>* get_entities();

private:
    void die(Entity& entity, int index);
    void update_last_safe(Entity& entity);

    bool m_entities_changed;
    bool m_player_died;

    std::list<Entity>* m_entities;
    std::map<int, Tile*> m_tiles;
};


#endif //DAB_HEALTH_SYSTEM_HPP
