#include "storyline.hpp"

StoryLine::StoryLine() {
}

bool StoryLine::init() {
    m_background_music = Mix_LoadMUS(audio_path("mainmenu.wav"));
    Scene::init();
    return true;
}

void StoryLine::on_key(int key, int action) {
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        m_scene_change_callback();
    }
}