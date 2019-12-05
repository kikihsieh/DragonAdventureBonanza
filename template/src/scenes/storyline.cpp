#include "storyline.hpp"

StoryLine::StoryLine() {
}

void StoryLine::draw(const mat3& projection) {
    m_rendersystem->draw_all(projection);
    m_rendersystem->render_text("Press s to continue", projection, {500,700}, {1.0, 1.0, 1.0});
}


void StoryLine::on_key(int key, int action) {
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        m_scene_change_callback();
    }
}