#include <cmath>
#include "camera.hpp"

void Camera::init(vec2 dim) {
    m_dim = dim;
    m_center.x = dim.x / 2.0f;
    m_center.y = dim.y / 2.0f;

    m_snap_speed = 12.f;
    m_offset_x = m_dim.x / 8.f;
}

void Camera::update(vec2 player_pos, bool moving_forwards) {
    if (moving_forwards) {
        float forwards_center_x = player_pos.x + m_offset_x;
        if (m_center.x < forwards_center_x) {
            m_center.x = fmin(m_center.x + m_snap_speed, forwards_center_x);
        }
    } else {
        float backwards_center_x = player_pos.x - m_offset_x;
        if (m_center.x > backwards_center_x) {
            m_center.x = fmax(m_center.x - m_snap_speed, backwards_center_x);
        }
    }
}

float Camera::compute_translation_x() {
    return (-2.0f * m_center.x / m_dim.x);
}
