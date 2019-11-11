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
#include <ecs/entities/modal.h>
#include <ecs/entities/button.hpp>

class Scene
{
public:
    Scene();
    virtual ~Scene() = default;

    // Creates all the associated render resources and default transform
    virtual bool init();

    // Releases all associated resources
    virtual void destroy();

    virtual void update(float elapsed_ms, vec2 screen_size);

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

    void on_key(int key, int action);
    Button* on_mouse(int key, int action, double xpos, double ypos);

    std::list<Entity> m_entities;
    std::list<Button> m_buttons; // TODO: should probably be a protected member// TODO: should probably be a protected member
    bool drawHelp = false;
    bool paused = false;
protected:
    virtual const char * get_bg_texture_path() = 0;

	RenderSystem* m_rendersystem;
    InputSystem *m_inputsystem;
    Modal help = Modal(textures_path("help_menu.png"));
};
#endif
