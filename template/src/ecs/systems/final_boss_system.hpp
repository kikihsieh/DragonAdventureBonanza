#ifndef DAB_FINAL_BOSS_SYSTEM_HPP
#define DAB_FINAL_BOSS_SYSTEM_HPP

#include <ecs/entities/entity.hpp>
#include <list>

class FinalBossSystem {
public:
    bool init(Entity final_boss, std::list<Entity> *entities);

    void update(float ms);

private:

    void phase_1 (float ms);

    float m_phase_1_timer;
    float m_phase_1_frequency;

    Entity m_final_boss;

    std::list<Entity>* m_entities;
};

#endif //DAB_FINAL_BOSS_SYSTEM_HPP
