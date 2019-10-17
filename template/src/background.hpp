#pragma once

#include <ecs/entities/entity.hpp>


class Background : public Entity
{
public:
     Background();
     ~Background();
	
	// Creates all the associated render resources and default transform
	 bool init(const char* path);

	// Releases all associated resources
	void destroy();
};
