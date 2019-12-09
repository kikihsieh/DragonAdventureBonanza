#pragma once

// internal
#include "common.hpp"
#include "ecs/systems/camera_system.hpp"
#include <scenes/levels/level.hpp>
#include <ecs/entities/button.hpp>
#include <scene_name.hpp>

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
    
    enum Sound_sfx{
        CLICK,
        SHOOT,
        JUMP,
        P_DAMAGE,
        ENEMY_DAMAGE,
        ENEMY_DAMAGE2,
        KEY_PRESS,
        TORCH,
        HEART,
        WOW,
    };

	// Creates a window, sets up events and begins the game
	bool init(vec2 screen);

	// Releases all associated resources
	void destroy();

	// Steps the game ahead by ms milliseconds
	bool update(float ms);

	// Renders our scene
	void draw();
	void draw(bool loading);

	// Should the game be over ?
	bool is_over()const;

    static void playSFX(Sound_sfx sound);
    
	
private:
    bool load_scene(Scene_name scene);
    
	// !!! INPUT CALLBACK FUNCTIONS
	void on_key(GLFWwindow*, int key, int, int action, int mod);
	void on_mouse_move(GLFWwindow* window, double xpos, double ypos);
	void on_mouse_click(GLFWwindow* window, int key, int action, int mod);

	int save();
	int load();

	void change_scene();

private:
	// Window handle
	GLFWwindow* m_window;
	float m_screen_scale; // Screen to pixel coordinates scale factor

	// Screen texture
	// The draw loop first renders to this texture, then it is used for the water shader
	GLuint m_frame_buffer;
	Texture m_screen_tex;

    Scene_name m_current_scene;

    std::map<Scene_name, Scene*> m_scenes;
    std::map<Scene_name, bool> m_unlocked_levels;
    
    std::map<Sound_sfx, Mix_Chunk*> m_sfx;
    std::string m_save_path;
    static World* w;
};
