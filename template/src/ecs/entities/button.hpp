#ifndef DAB_BUTTON_H
#define DAB_BUTTON_H

#include "entity.hpp"

struct Button : public Entity {

    Button(){
        scale = {1.f, 1.f};

        drawable = new Drawable();
        drawable->texture_path = textures_path("start.png");
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");

		input = new Input();
        
        position =  {600.f,400.f};
    }
};

#endif //DAB_BUTTON_H
