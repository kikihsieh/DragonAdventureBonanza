#include "input_system.hpp"
#include <vector>
#include <map> 
#include <sstream>
#include <cmath>

void InputSystem::update(std::map<const char*, bool> *input_updates) {
    for (auto &entity : *m_entities) {
        if (!entity.input) {
            continue;
        }
        
        if (&input_updates->at("UP")){
            entity.input->up_pressed = true;
        } else{
            entity.input->up_pressed = false;
        }
        if (&input_updates->at("RIGHT")){
            entity.input->right_pressed = true;
        } else {
            entity.input->right_pressed = false;
        }
        if (&input_updates->at("LEFT")){
            entity.input->left_pressed = true;
        } else {
            entity.input->left_pressed = false;
        }
        if (&input_updates->at("SHIFT_LEFT")){
            entity.input->shift_left = true;
        } else {
            entity.input->shift_left = false;
        }
        if (&input_updates->at("SHIFT_RIGHT")){
            entity.input->shift_right = true;
        } else {
            entity.input->shift_right = false;
        }
    }
}

bool InputSystem::init(std::vector<Entity> *entities) {
    m_entities = entities;
    return true;
}