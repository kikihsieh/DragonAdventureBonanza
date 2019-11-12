#pragma once

// internal
#include "common.hpp"
#include "ecs/systems/camera_system.hpp"
#include <scenes/levels/level.hpp>
#include <ecs/entities/button.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

// Container for all our entities and game logic. Individual rendering / update is
// deferred to the relative update() methods
class World
{
public:
    enum Scene_names {
        MAIN_MENU,
        FOREST,
        VOLCANO,
        HELP,
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
    bool load_scene(Scene* scene);
    
	// !!! INPUT CALLBACK FUNCTIONS
	void on_key(GLFWwindow*, int key, int, int action, int mod);
	void on_mouse_move(GLFWwindow* window, double xpos, double ypos);
	void on_mouse_click(GLFWwindow* window, int key, int action, int mod);

private:
	// Window handle
	GLFWwindow* m_window;
	float m_screen_scale; // Screen to pixel coordinates scale factor

	// Screen texture
	// The draw loop first renders to this texture, then it is used for the water shader
	GLuint m_frame_buffer;
	Texture m_screen_tex;

    // Game entities
    Scene* m_current_scene;
    std::map<std::string, Scene*> m_scenes;
};
