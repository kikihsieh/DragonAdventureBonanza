#pragma once

// internal
#include "common.hpp"
#include "player.hpp"
#include "enemies/spider.hpp"
#include "background.hpp"
#include "ground.hpp"
#include "camera.hpp"
#include "platform.hpp"
#include "levels/tile.hpp"

// stlib
#include <vector>
#include <random>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>
#include <levels/level.hpp>

// Container for all our entities and game logic. Individual rendering / update is
// deferred to the relative update() methods
class World
{
public:
    enum Scene {
        MAIN_MENU,
        FOREST,
        VOLCANO,
        CAVE,
        SNOW_MOUNTAIN,
        NIGHT_SKY
    };

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

private:
    bool load_scene(Level* level);
    
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
    Level* m_current_scene;
    std::map<Scene, Level*> m_scenes;

    Player m_player;
    Background m_background;
    Camera m_camera;
};
