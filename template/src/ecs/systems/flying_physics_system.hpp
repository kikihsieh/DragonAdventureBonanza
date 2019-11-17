#ifndef DAB_FLYING_PHYSICS_SYSTEM_HPP
#define DAB_FLYING_PHYSICS_SYSTEM_HPP

#include <list>
#include "physics_system.hpp"

class FlyingPhysicsSystem : public PhysicsSystem {
public:
    bool init(std::list<Entity> *entities, vec2 level_bounds) override;

    void update(float ms) override;

private:
    void move(float ms, Entity& entity) override;

    std::list<Entity>* m_entities;

    vec2 m_level_bounds_x;
    vec2 m_level_bounds_y;
};


#endif //DAB_FLYING_PHYSICS_SYSTEM_HPP
