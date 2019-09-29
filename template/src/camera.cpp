#include "camera.hpp"

bool Camera::init(vec2 dim) {
    m_dim = dim;
    m_center.x = dim.x / 2.0f;
    m_center.y = dim.y / 2.0f;
    return true;
}

void Camera::update(vec2 player_pos) {
    m_center = player_pos;
}

float Camera::compute_translation_x() {
    return -2.0f * m_center.x / m_dim.x;
}
