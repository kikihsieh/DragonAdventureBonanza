#include "camera_system.hpp"

CameraSystem::CameraSystem(){}

CameraSystem::~CameraSystem() = default;

bool CameraSystem::init(vec2 dim){
    m_dim = dim;
    m_center.x = dim.x / 2.0f;
    m_center.y = dim.y / 2.0f;

    m_offset_x = m_dim.x / 8.f;

    m_snap_speed = 12.f;
    m_snap_dist = m_dim.x / 4.f;

    m_snap_threshold_f = true;
    m_snap_threshold_b = false;
	
	return true;
}

void CameraSystem::update(vec2 player_pos, bool moving_forwards){
    if (moving_forwards) {
        m_snap_threshold_b = false;
        if (m_snap_threshold_f) {
            m_center.x = fmin(m_center.x + m_snap_speed, player_pos.x + m_offset_x);
        } else if (player_pos.x > (m_center.x + m_snap_dist)) {
            m_snap_threshold_f = true;
        }
    } else {
        m_snap_threshold_f = false;
        if (m_snap_threshold_b) {
            m_center.x = fmax(m_center.x - m_snap_speed, player_pos.x - m_offset_x);
        } else if (player_pos.x < (m_center.x - m_snap_dist)) {
            m_snap_threshold_b = true;
        }
    }
}

void CameraSystem::reset(){
    m_center.x = m_dim.x / 2.0f;
    m_center.y = m_dim.y / 2.0f;

    m_snap_threshold_f = true;
    m_snap_threshold_b = false;
}

float CameraSystem::compute_translation_x(){
    return -2.0f * m_center.x / m_dim.x;
}