#ifndef DAB_FLYING_PHYSICS_SYSTEM_HPP
#define DAB_FLYING_PHYSICS_SYSTEM_HPP

#include <list>
#include "physics_system.hpp"
#include "final_boss_spawning_system.hpp"

class FlyingPhysicsSystem : public PhysicsSystem {
public:
    bool init(std::list<Entity> *entities, vec2 level_bounds) override;

    void update(float ms) override;

    void set_spawning_system(FinalBossSpawningSystem* final_boss_spawning_system);

private:
    void move(float ms, Entity& entity) override;

    std::list<Entity>* m_entities;

    vec2 m_level_bounds_x;
    vec2 m_level_bounds_y;

    FinalBossSpawningSystem* m_final_boss_spawning_system;
};


#endif //DAB_FLYING_PHYSICS_SYSTEM_HPP
