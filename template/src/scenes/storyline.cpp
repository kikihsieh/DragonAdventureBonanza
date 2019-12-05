#include "storyline.hpp"

StoryLine::StoryLine() {
}

void StoryLine::on_key(int key, int action) {
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        m_scene_change_callback();
    }
}