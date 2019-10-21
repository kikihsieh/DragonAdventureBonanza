#include "input_system.hpp"
#include <list>
// #include <iostream>

bool InputSystem::init(std::list<Entity> *entities) {
    m_entities = entities;
    return true;
}

void InputSystem::on_key_update(int key, int action) {
    for (auto &entity : *m_entities) {
        if (!entity.input) {
            continue;
        }

        if (key == GLFW_KEY_UP || key == GLFW_KEY_W) {
            if (action == GLFW_PRESS){
                entity.input->up = true;
            } else if (action == GLFW_RELEASE ) {
                entity.input->up = false;
            }
        }
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
            if (action == GLFW_PRESS) {
                entity.input->left = true;
            } else if (action == GLFW_RELEASE ) {
                entity.input->left = false;
            }
        }

        if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
            if (action == GLFW_PRESS) {
                entity.input->right = true;
            } else if (action == GLFW_RELEASE) {
                entity.input->right = false;
            }
        }

        if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) {
            if (action == GLFW_PRESS) {
                entity.input->shift = true;
            } else if (action == GLFW_RELEASE) {
                entity.input->shift = false;
            }
        }
    }
}

void InputSystem::on_mouse_update(int key, int action, double xpos, double ypos){
    for (auto &entity : *m_entities) {
        if (!entity.input) {
            continue;
        }

        if (key == GLFW_MOUSE_BUTTON_LEFT){
            if (action == GLFW_PRESS){
                entity.input->mouse_left = true;
                // TODO: print out to check mouse event works, need to update here once button is updated
                // std::cout << "left clicked" << std::endl;
            } else {
                entity.input -> mouse_left = false;
            }
        }
    }
}
