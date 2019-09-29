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
	void update(float ms);
	
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

	// Moves the player's position by the specified offset
	void move(vec2 off);

	// True if the player is alive
	bool is_alive()const;

	// Kills the player, changing its alive state and triggering on death events
	void kill();
    
    // Set player direction
    void set_direction(vec2 dir);

	// Check if player is landed
	void land(const Ground& ground);
    
    // Check if player is landed
    void platformCollision(const Platform& platform);
    
    vec2 m_direction;

	// TODO: use vector when we change to use mesh file
	void compute_world_coordinate();
    
    bool m_on_ground; // True if player is on ground/platform
    bool m_is_jumping; // True if player is on ground/platform
    
    float topSide;
    float bottomSide;
    float rightSide;
    float leftSide;

private:
	bool m_is_alive; // True if the player is alive
	Texture player_texture;
	std::vector<vec2> player_world_coord;
	TexturedVertex vertices[4];
};
