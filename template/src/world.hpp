#pragma once

// internal
#include "common.hpp"
#include "player.hpp"
#include "spider.hpp"
#include "background.hpp"
#include "ground.hpp"
#include "camera.hpp"
#include "platform.hpp"
#include "tile.hpp"

// stlib
#include <vector>
#include <random>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>



// Container for all our entities and game logic. Individual rendering / update is 
// deferred to the relative update() methods
class World
{
public:
	World();
	~World();

	// Creates a window, sets up events and begins the game
	bool init(vec2 screen);

	// Releases all associated resources
	void destroy();

	// Steps the game ahead by ms milliseconds
	bool update(float ms);

	// Renders our scene
	void draw();

	// Should the game be over ?
	bool is_over()const;
    
    bool setTextures();

private:
    // Generates a new spider
    //bool init_enemies(float& scale, int& w, int& h);
    bool init_enemies(int x, int y);
    bool spawn_spider();
    
    //Load tiles
    bool loadLevel(int arr[17][50]);
    bool drawMap();
    int map[17][50];
    
	// !!! INPUT CALLBACK FUNCTIONS
	void on_key(GLFWwindow*, int key, int, int action, int mod);
	void on_mouse_move(GLFWwindow* window, double xpos, double ypos);

private:
	// Window handle
	GLFWwindow* m_window;
	float m_screen_scale; // Screen to pixel coordinates scale factor

	// Screen texture
	// The draw loop first renders to this texture, then it is used for the water shader
	GLuint m_frame_buffer;
	Texture m_screen_tex;

    // Game entities
    std::vector<Spider> m_spiders;
    std::vector<Tile> m_tiles;
    
  	vec2 m_x_boundaries;
    vec2 m_y_boundaries;

    Player m_player;
    Background m_background;
    Ground m_ground;
    Camera m_camera;
    Platform m_platform;
    
    Texture tile1_texture;
    Texture tile1_left_texture;
    Texture tile1_right_texture;
    Texture tile1_left_corner_texture;
    Texture tile1_right_corner_texture;
    Texture tile1_left_end_texture;
    Texture tile1_right_end_texture;
    Texture tile2_texture;
    
    Texture spider_texture;
    
	// C++ rng
	std::default_random_engine m_rng;
	std::uniform_real_distribution<float> m_dist; // default 0..1
};
