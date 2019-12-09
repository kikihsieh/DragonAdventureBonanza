#include "camera_system.hpp"
#include <cmath>

CameraSystem::CameraSystem(){}

CameraSystem::~CameraSystem() = default;

bool CameraSystem::init(vec2 level_dim, vec2 screen_size, bool vertical_enabled){
    m_level_dim = level_dim;

    m_center = {screen_size.x*0.5f, m_level_dim.y - (screen_size.y * 0.5f)};

    m_horizontal_snap_speed = 750.f;
    m_vertical_snap_speed = 600.f;

    m_target_y_pos = m_center.y;

    m_snap_threshold_f = true;
    m_snap_threshold_b = false;

    m_vertical_enabled = vertical_enabled;

	return true;
}

void CameraSystem::update(float ms, Player* player, vec2 screen_size) {
    update_x(ms, player, screen_size);

    if (!m_vertical_enabled) {
        m_center.y = m_level_dim.y - (screen_size.y * 0.5f);
    } else {
        update_y(ms, player, screen_size);
    }
}

void CameraSystem::update_x(float ms, Player *player, vec2 screen_size) {
    m_offset_x = screen_size.x / 8.f;
    m_horizontal_snap_dist = screen_size.x / 4.f;

    if (player->physics->velocity.x > 0) {
        m_snap_threshold_b = false;
        if (m_snap_threshold_f) {
            m_center.x = fmin(m_center.x + m_horizontal_snap_speed * (ms / 1000), player->position.x + m_offset_x);
        } else if (player->position.x > (m_center.x + m_horizontal_snap_dist)) {
            m_snap_threshold_f = true;
        }
    } else {
        m_snap_threshold_f = false;
        if (m_snap_threshold_b) {
            m_center.x = fmax(m_center.x - m_horizontal_snap_speed * (ms / 1000), player->position.x - m_offset_x);
        } else if (player->position.x < (m_center.x - m_horizontal_snap_dist)) {
            m_snap_threshold_b = true;
        }
    }

    if (m_center.x + screen_size.x * 0.5f > m_level_dim.x) {
        m_center.x = m_level_dim.x - screen_size.x * 0.5f;
    } else if (m_center.x - screen_size.x * 0.5f < 0) {
        m_center.x = screen_size.x * 0.5f;
    }
}

void CameraSystem::update_y(float ms, Player *player, vec2 screen_size) {
    m_vertical_snap_dist = screen_size.y / 5.f;

    if (player->physics->jump_count == 0 && abs(player->position.y - m_center.y) > m_vertical_snap_dist) {
        m_target_y_pos = player->position.y;
    }

    if (m_center.y > m_target_y_pos) {
        m_center.y = fmax(m_center.y - m_vertical_snap_speed * (ms / 1000), m_target_y_pos);
    } else {
        m_center.y = fmin(m_center.y + m_vertical_snap_speed * (ms / 1000), m_target_y_pos);
    }
    if (m_center.y - screen_size.y * 0.5f < 0) {
        m_center.y = screen_size.y * 0.5f;
    } else if (m_center.y + screen_size.y * 0.5f > m_level_dim.y) {
        m_center.y = m_level_dim.y - screen_size.y * 0.5f;
    }
}

float CameraSystem::compute_translation_x(vec2 screen_size){
    return -2.0f * m_center.x / screen_size.x;
}

float CameraSystem::compute_translation_y(vec2 screen_size){
    return 2.0f * m_center.y / screen_size.y;
}
