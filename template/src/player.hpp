#pragma once

#include "common.hpp"
#include <vector>

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

	// Moves the player's position by the specified offset
	void move(vec2 off);

	// True if the player is alive
	bool is_alive()const;

	// Kills the player, changing its alive state and triggering on death events
	void kill();
    
    // Set player direction
    void set_direction(vec2 dir);
    
    vec2 m_direction;
    
    bool m_on_ground; // True if player is on ground/platform
    bool m_is_jumping; // True if player is on ground/platform

private:
	bool m_is_alive; // True if the player is alive
	Texture player_texture;
};
