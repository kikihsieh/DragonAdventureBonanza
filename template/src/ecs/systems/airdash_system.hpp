#ifndef DAB_AIRDASH_SYSTEM_HPP
#define DAB_AIRDASH_SYSTEM_HPP

#include <map>
#include <list>
#include <ecs/entities/entity.hpp>

class AirDashSystem {
public:
	bool init(std::list<Entity> *entities);
	void update(float ms);

private:
	void airdash(Entity& entity);
	void stop_airdash(Entity& entity);

	bool can_airdash(Entity& entity);
	bool is_airdashing(Entity& entity);

private:
	std::list<Entity>* m_entities;
};

#endif //DAB_AIRDASH_SYSTEM_HPP
