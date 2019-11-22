#include "airdash_system.hpp"

void AirDashSystem::update(float ms) {

    for (auto &entity : *m_entities) {
        if (!entity.airdash || !entity.physics || !entity.collider || !entity.input) {
            continue;
        }

        if (entity.input->shift && can_airdash(entity)) {
            airdash(entity);
        }

        if (is_airdashing(entity)) {
            entity.physics->velocity.x = entity.airdash->cur_airdash_speed;
            entity.airdash->cur_airdash_speed -=
                    entity.is_facing_forward ?
                    (ms / 1000.f) * entity.airdash->airdash_friction :
                    (ms / -1000.f) * entity.airdash->airdash_friction;

            if ((entity.is_facing_forward && entity.airdash->cur_airdash_speed <= 0.f) ||
                    (!entity.is_facing_forward && entity.airdash->cur_airdash_speed >= 0.f)) {
                stop_airdash(entity);
            }
        }

        if (entity.collider->left || entity.collider->bottom || entity.collider->top || entity.collider->right)
            stop_airdash(entity);
    }
}


bool AirDashSystem::init(std::list<Entity> *entities) {
    m_entities = entities;
    return true;
}


void AirDashSystem::airdash(Entity& entity) {
    entity.airdash->cur_airdash_speed = entity.is_facing_forward ? entity.airdash->base_airdash_speed : -1.f * entity.airdash->base_airdash_speed;
    entity.physics->velocity.y = 0;
    entity.physics->acceleration.y = 0;
    entity.physics->velocity.x = 0;
    entity.airdash->airdashing = true;
    entity.airdash->can_airdash = false;
}



void AirDashSystem::stop_airdash(Entity& entity) {
    entity.airdash->airdashing = false;
    entity.airdash->cur_airdash_speed = 0;
    entity.physics->acceleration.y = entity.physics->gravity;
}



bool AirDashSystem::can_airdash(Entity& entity) {
    return entity.airdash->can_airdash && !entity.physics->grounded;
}


bool AirDashSystem::is_airdashing(Entity& entity) {
    return entity.airdash->airdashing;
}

