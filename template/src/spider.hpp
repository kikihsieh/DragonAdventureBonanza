#pragma once

#include "common.hpp"
#include <vector>

// spider enemy
class Spider : public Entity
{
	// Shared between all enemies, no need to load one for each instance
	static Texture spider_texture;

public:
    
	// Creates all the associated render resources and default transform
	bool init();

	// Releases all the associated resources
	void destroy();
    
    //walking boundary 
    void boundary(vec2 position);
    
    //spider jumping @ random time
    void jump_Now(vec2, float);
    
    //generate random time 
    int jump_Time(float step);

	// Update spider due to current
	// ms represents the number of milliseconds elapsed from the previous update() call
	void update(float ms);

    
	// projection is the 2D orthographic projection matrix
	void draw(const mat3& projection) override;

	// Returns the current spider position
	vec2 get_position()const;

	// Sets the new spider position
	void set_position(vec2 position);

	// Returns the spider's bounding box for collision detection, called by collides_with()
	vec2 get_bounding_box() const;
    
    int distance;
    int min_position;
    int max_position;
    int distance_y;
    int min_position_y;
    int max_position_y;
    
    int inital_pos;
    bool direction;
    bool direction_y;
    bool jumpNow;
    int jumpT;
    float currTime;
    
    bool randomBoo;
    
};

