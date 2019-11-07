#pragma once

#include "entity.hpp"
#include <list>

struct Bat : public Entity {
    Bat(std::shared_ptr<Texture> texture, vec2 pos) {
        scale = { 1.f, 1.f };

        drawable = new Drawable();
        drawable->texture_path = textures_path("bat1.png");
        drawable->fs_shader = shader_path("textured.fs.glsl");
        drawable->vs_shader = shader_path("textured.vs.glsl");
        drawable->texture = texture;

        position = pos;
        
        //collider = new Collider();
        is_facing_forward = true;
        
        flyable = new Flyable();
        flyable->flyable_enemy = true;
        
        enemyai = new EnemyAI();
       

        const TexturePathMapping m_texture_map = {
            { 0, textures_path("bat1.png")},
            { 1, textures_path("bat2.png")},
            { 2, textures_path("bat3.png")},
            { 3, textures_path("bat4.png")}
        };
         animatable = new Animatable(m_texture_map);
         animatable->index = 0;
        
        
    }
};
