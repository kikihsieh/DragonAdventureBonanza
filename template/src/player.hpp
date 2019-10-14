#pragma once

#include "common.hpp"
#include "spider.hpp"
#include <vector>

class Tile;

class Player : public Entity
{
public:
	// Creates all the associated render resources and default transform
	bool init(vec2 x_bounds, vec2 y_bounds);

	// Releases all associated resources
	void destroy();
	
	// Update player position based on direction
	// ms represents the number of milliseconds elapsed from the previous update() call
	void update(float ms, std::vector<Tile> m_tiles);
	
	// Renders the player
	void draw(const mat3& projection)override;

// ========================================
// TODO: collision code
// ========================================
	// Collision routine
//	bool collides_with(const Turtle& turtle);

	// Returns the current player position
	vec2 get_position() const;
	bool is_facing_forwards() {
	    return m_is_facing_forwards;
	}

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
	void air_dash(bool forward);
	
	// Check if player is landed
	bool can_jump();
	
	bool can_airdash();
	bool is_airdashing();

	// TODO: use vector when we change to use mesh file
	void compute_world_coordinate();
    
  	// Check if player is landed
  	void platformCollision(const Tile& platform);

	bool collides_with(Spider& spider);

	bool kill_enemy;

private:
	bool m_is_alive; // True if the player is alive
    bool m_on_ground; // True if player is on ground/platform
	bool m_unlocked_double_jump;
	bool m_stopped_airdash;
	int m_jump_count;
	
	bool m_airdashing;
	
    bool m_is_facing_forwards; // True if player is facing forward

    float walking_speed;
    float jumping_speed;
    float gravity;
	
	float top;
	float bottom;
	float left;
	float right;
	
	float m_airdash_duration;
	float m_airdash_timer;
	
	vec2 m_x_world_bounds;
	vec2 m_y_world_bounds;
	
    Texture player_texture;
	std::vector<vec2> player_world_coord;
	TexturedVertex vertices[4];
};
