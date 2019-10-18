#include "input_system.hpp"
#include <vector>

bool InputSystem::init(std::vector<Entity> *entities) {
    m_entities = entities;
    return true;
}

void InputSystem::update(int key, int action) {
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
    }
}
