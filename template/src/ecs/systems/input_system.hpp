#pragma once

#include <list>
#include "../entities/entity.hpp"
#include <ecs/entities/button.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

class InputSystem {
public:
    
    ~InputSystem();

    bool init(std::list<Entity>* entities, std::list<Button>* buttons);
    void on_key_update(int key, int action);
    void on_mouse_update(int key, int action, double xpos, double ypos);
    
private:
    std::list<Entity>* m_entities;
    std::list<Button>* m_buttons;

    void mouse_sfx();
    Mix_Chunk* m_click;
    Mix_Chunk* m_jump;
    Mix_Chunk* m_shoot;
};
