#ifndef DAB_PHYSICS_SYSTEM_HPP
#define DAB_PHYSICS_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>

class PhysicsSystem {
public:
    bool init(std::list<Entity> *entities, vec2 level_bounds);

    void update(float ms);

private:
    void move(float ms, Entity& entity);

    std::list<Entity>* m_entities;

    vec2 m_level_bounds_x;
    vec2 m_level_bounds_y;
};

#endif //DAB_PHYSICS_SYSTEM_HPP
