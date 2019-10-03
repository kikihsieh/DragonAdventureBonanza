#pragma once

#include "common.hpp"
#include <vector>

class Ground;
class Platform;

class Player : public Entity
{
public:
	// Creates all the associated render resources and default transform
	bool init();

	// Releases all associated resources
	void destroy();
	
	// Update player position based on direction
	// ms represents the number of milliseconds elapsed from the previous update() call
	void update(float ms, const Platform& platform);
	
	// Renders the player
	void draw(const mat3& projection)override;

// ========================================
// TODO: collision code
// ========================================
	// Collision routine
//	bool collides_with(const Turtle& turtle);

	// Returns the current player position
	vec2 get_position() const;
    
    void set_position(vec2 pos);
    
    vec2 get_speed() const;

	// Moves the player's position by the specified offset
	void move(vec2 off);

	// True if the player is alive
	bool is_alive()const;

	// Kills the player, changing its alive state and triggering on death events
	void kill();
    
    // Set player direction
    void walk(bool forward);
    void stop();
    void jump();

	// Check if player is landed
	void land(const Ground& ground, const Platform& platform);


	bool can_jump();

	// TODO: use vector when we change to use mesh file
	void compute_world_coordinate();
    
    vec2 get_bounding_box() const;
    
    // Check if player collides with platform
    void platformCollision(const Platform& platform);

private:
	bool m_is_alive; // True if the player is alive
    bool m_on_ground; // True if player is on ground/platform
    bool m_is_collide; //True if player collide with platform
    bool m_on_platform; // True if player on top of platform

    float walking_speed;
    float jumping_speed;
    float gravity;

    Texture player_texture;
	std::vector<vec2> player_world_coord;
	TexturedVertex vertices[4];
};
