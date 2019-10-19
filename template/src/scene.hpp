//
// Created by arden on 10/14/2019.
//
#ifndef DAB_SCENE_HPP
#define DAB_SCENE_HPP

#include <list>
#include <map>
#include <ecs/systems/render_system.hpp>
#include <ecs/systems/input_system.hpp>

class Scene
{
public:
    Scene();
    ~Scene();

    // Creates all the associated render resources and default transform
    virtual bool init();

    // Releases all associated resources
    virtual void destroy();

    virtual void update(float elapsed_ms);

    virtual void draw(const mat3& projection);
    virtual bool is_level();

    virtual vec2 get_player_position() = 0;
    virtual bool is_forward() = 0;

    void on_key(int key, int action);
    void on_mouse(int key, int action, double xpos, double ypos);

    std::list<Entity> m_entities; // TODO: should probably be a protected member
protected:
    virtual const char * get_bg_texture_path() = 0;

	RenderSystem m_rendersystem;
    InputSystem *m_inputsystem;
};
#endif
