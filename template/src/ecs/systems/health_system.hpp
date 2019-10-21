#ifndef DAB_HEALTH_SYSTEM_HPP
#define DAB_HEALTH_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>

class HealthSystem {
public:
    bool init(std::list<Entity> *entities);

    void update(float ms);

private:
    void die(Entity& entity);

    std::list<Entity>* m_entities;
};


#endif //DAB_HEALTH_SYSTEM_HPP
