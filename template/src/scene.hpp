//
// Created by arden on 10/14/2019.
//
#ifndef DAB_SCENE_HPP
#define DAB_SCENE_HPP

#include "common.hpp"

class Scene: public Entity
{
public:
    Scene();
    ~Scene();

    // Creates all the associated render resources and default transform
    virtual bool init(const char* path);

    // Releases all associated resources
    virtual void destroy();

    virtual void update(float elapsed_ms);

    virtual void draw(const mat3& projection);
    virtual bool is_level();
    virtual const char * get_bg_texture_path() = 0;

private:
    Texture* m_texture;
};
#endif
