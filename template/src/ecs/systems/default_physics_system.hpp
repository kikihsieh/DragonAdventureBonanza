#ifndef DAB_DEFAULT_PHYSICS_SYSTEM_HPP
#define DAB_DEFAULT_PHYSICS_SYSTEM_HPP

#include <list>
#include <ecs/entities/entity.hpp>
#include <ecs/systems/physics_system.hpp>

class DefaultPhysicsSystem : public PhysicsSystem {
public:

    explicit DefaultPhysicsSystem(bool double_jump);

    bool init(std::list<Entity> *entities, vec2 level_bounds) override;

    void update(float ms) override;

private:
    void move(float ms, Entity& entity) override;

    std::list<Entity>* m_entities;

    vec2 m_level_bounds_x;
    vec2 m_level_bounds_y;
};

#endif //DAB_DEFAULT_PHYSICS_SYSTEM_HPP
