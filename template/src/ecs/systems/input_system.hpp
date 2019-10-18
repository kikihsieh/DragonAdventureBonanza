#pragma once

#include <vector>
#include "../entities/entity.hpp"

class InputSystem {
public:
    bool init(std::vector<Entity>* entities);
    void on_key_update(int key, int action);
    void on_mouse_update(int key, int action, double xpos, double ypos);
    
private:
    std::vector<Entity>* m_entities;
};