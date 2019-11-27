//
// Created by arden on 10/14/2019.
//
#ifndef DAB_SCENE_HPP
#define DAB_SCENE_HPP

#include <list>
#include <map>
#include <ecs/systems/render_system.hpp>
#include <ecs/systems/input_system.hpp>
#include <ecs/entities/player.hpp>
#include <ecs/entities/modal.hpp>
#include <ecs/entities/button.hpp>
#include "../src/scene_name.hpp"
#include <functional>

class Scene
{
public:
    enum State {
        LOADING,
        LOADED,
        RUNNING,
        PAUSED
    };

    Scene();
    virtual ~Scene() = default;

    // Creates all the associated render resources and default transform
    virtual bool init();

    // Releases all associated resources
    virtual void destroy();

    virtual void update(float elapsed_ms, vec2 screen_size);
    virtual std::map<int, Tile*>* get_tiles();

    virtual void draw(const mat3& projection);
    virtual bool is_level();

    virtual float get_translation_x(vec2 screen_size) {
        float left = 0;
        float right = screen_size.x;
        return -(right + left) / (right - left);
    }

    virtual float get_translation_y(vec2 screen_size) {
        float top = 0;
        float bottom = screen_size.y;
        return -(top + bottom) / (top - bottom);
    }

    void addSceneChangeHandler(std::function<void(void)> callback);
    void loadSceneHandler(std::function<void(Scene_name)> callback);
    void exitGameHandler(std::function<void()> callback);

    void on_key(int key, int action);
    virtual void on_mouse(int key, int action, double xpos, double ypos);

    std::list<Entity> m_entities;
    std::list<Button> m_buttons;
    bool drawHelp = false;
    State state = LOADING;
    std::map<Scene_name, bool>* m_unlocked_levels;

protected:
    virtual const char * get_bg_texture_path() = 0;

	RenderSystem* m_rendersystem;
    InputSystem *m_inputsystem;
    Modal help = Modal(textures_path("modals/help_menu.png"));

    std::map<int, Tile*> m_tiles;

    std::function<void(void)> m_scene_change_callback;
    std::function<void(Scene_name)> load_scene;
    std::function<void(void)> exit_game;
    vec2 m_screen_size;
};
#endif
