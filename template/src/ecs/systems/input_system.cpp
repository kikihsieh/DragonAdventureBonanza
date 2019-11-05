#include "input_system.hpp"
#include <list>

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
            if (action == GLFW_PRESS) {
                entity.input->up = true;
            } else if (action == GLFW_RELEASE) {
                entity.input->up = false;
            }
        }
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
            if (action == GLFW_PRESS) {
                entity.input->left = true;
            } else if (action == GLFW_RELEASE) {
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

void InputSystem::on_mouse_update(int key, int action, double xpos, double ypos) {
    for (auto &entity : *m_entities) {
        if (!entity.input) {
            continue;
        }
        float width = entity.drawable->texture->width * 0.5f * entity.scale.x;
        float height = entity.drawable->texture->height * 0.5f * entity.scale.y;

        float top = entity.position.y + height;
        float bottom = entity.position.y - height;
        float left = entity.position.x - width;
        float right = entity.position.x + width;

        if (key == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                if (xpos > left && xpos < right &&
                    ypos < top && ypos > bottom)
                    entity.input->mouse_left = true;
                printf("left mouse click\n");
            } else {
                entity.input->mouse_left = false;
            }
        }
    }
}
