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

class Scene
{
public:
    Scene();
    virtual ~Scene() = default;

    // Creates all the associated render resources and default transform
    virtual bool init();

    // Releases all associated resources
    virtual void destroy();

    virtual void update(float elapsed_ms);

    virtual void draw(const mat3& projection);
    virtual bool is_level();

    void on_key(int key, int action);
    void on_mouse(int key, int action, double xpos, double ypos);

    std::list<Entity> m_entities; // TODO: should probably be a protected member
    bool drawHelp = false;
protected:
    virtual const char * get_bg_texture_path() = 0;

	RenderSystem* m_rendersystem;
    InputSystem *m_inputsystem;
    Modal help = Modal(textures_path("help_menu.png"));
};
#endif
