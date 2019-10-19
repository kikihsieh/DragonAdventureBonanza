#pragma once

#include <list>
#include "../entities/entity.hpp"

class InputSystem {
public:
    bool init(std::list<Entity>* entities);
    void on_key_update(int key, int action);
    void on_mouse_update(int key, int action, double xpos, double ypos);
    
private:
    std::list<Entity>* m_entities;
};