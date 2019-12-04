#ifndef DAB_PHYSICS_SYSTEM_HPP
#define DAB_PHYSICS_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>

class PhysicsSystem {
public:
    virtual ~PhysicsSystem() = default;;

    virtual bool init(std::list<Entity> *entities, vec2 level_bounds) = 0;

    virtual void update(float ms) = 0;

private:
    virtual void move(float ms, Entity& entity) = 0;

    std::list<Entity>* m_entities;

protected:
    bool m_double_jump;
};

#endif //DAB_PHYSICS_SYSTEM_HPP
