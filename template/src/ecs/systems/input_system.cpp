#include "input_system.hpp"

bool InputSystem::init(std::list<Entity> *entities, std::list<Button> *buttons) {
    m_entities = entities;
    m_buttons = buttons;
    m_sfx = Mix_LoadWAV(audio_path("/sfx/blreep_sound.wav"));
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
        if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
            if (action == GLFW_PRESS) {
                entity.input->down = true;
            } else if (action == GLFW_RELEASE) {
                entity.input->down = false;
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
        
        if (key == GLFW_KEY_SPACE) {
            if (action == GLFW_PRESS) {
                entity.input->space = true;
            } else if (action == GLFW_RELEASE) {
                entity.input->space = false;
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
    for (auto &entity : *m_buttons) {
        if (!entity.input) {
            continue;
        }
        entity.texture_size = {entity.drawable->texture->width * 1.f , entity.drawable->texture->height * 1.f};
        float width = entity.texture_size.x * entity.scale.x;
        float height = entity.texture_size.y * entity.scale.y;

        float top = entity.position.y + height/2.f;
        float bottom = entity.position.y - height/2.f;
        float left = entity.position.x - width/2.f;
        float right = entity.position.x + width/2.f;

        if (key == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                if (xpos > left && xpos < right &&
                    ypos < top && ypos > bottom) {
                    if (entity.active) {
                        mouse_sfx();
                        return entity.m_button_callback();
                    }
                }
            }
        }
    }
}

void InputSystem::mouse_sfx() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");
        return;
    }
    if (!m_sfx)
    {
        fprintf(stderr, "Failed to load sounds make sure the data directory is present");
        return;
    }

    Mix_PlayChannel(-1, m_sfx, 0);

    fprintf(stderr, "Loaded sfx\n");
}
