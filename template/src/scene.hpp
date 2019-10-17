//
// Created by arden on 10/14/2019.
//
#ifndef DAB_SCENE_HPP
#define DAB_SCENE_HPP

#include <vector>
#include "ecs/systems/render_system.hpp"

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
    virtual const char * get_bg_texture_path() = 0;

    std::vector<Entity> m_entities;

private:
	RenderSystem m_rendersystem;
};
#endif
