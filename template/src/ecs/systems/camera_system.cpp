#include "camera_system.hpp"
#include <cmath>

CameraSystem::CameraSystem(){}

CameraSystem::~CameraSystem() = default;

bool CameraSystem::init(vec2 screen_size){
    m_screen_size = screen_size;
    m_level_dim = screen_size;

    m_center = {0,0};

    m_offset_x = m_screen_size.x / 8.f;

    m_snap_speed = 12.f;
    m_snap_dist = m_screen_size.x / 4.f;

    m_snap_threshold_f = true;
    m_snap_threshold_b = false;
	
	return true;
}

void CameraSystem::update(vec2 player_pos, bool moving_forwards){
    if (moving_forwards) {
        m_snap_threshold_b = false;
        if (m_snap_threshold_f) {
            m_center.x = fmin(m_center.x + m_snap_speed, player_pos.x + m_offset_x);
            if (m_center.x + m_screen_size.x*0.5f > m_level_dim.x) {
                m_center.x = m_level_dim.x - m_screen_size.x*0.5f;
            }
        } else if (player_pos.x > (m_center.x + m_snap_dist)) {
            m_snap_threshold_f = true;
        }
    } else {
        m_snap_threshold_f = false;
        if (m_snap_threshold_b) {
            m_center.x = fmax(m_center.x - m_snap_speed, player_pos.x - m_offset_x);
            if (m_center.x - m_screen_size.x*0.5f < 0) {
                m_center.x = m_screen_size.x*0.5f;
            }
        } else if (player_pos.x < (m_center.x - m_snap_dist)) {
            m_snap_threshold_b = true;
        }
    }
    m_center.y = player_pos.y;
    if (m_center.y - m_screen_size.y*0.5f < 0) {
        m_center.y = m_screen_size.y*0.5f;
    } else if (m_center.y + m_screen_size.y*0.5f > m_level_dim.y) {
        m_center.y = m_level_dim.y - m_screen_size.y*0.5f;
    }
}

void CameraSystem::reset(vec2 level_dim){
    m_level_dim = level_dim;

    // Always reset to bottom left corner of map
    m_center.y = m_level_dim.y - m_screen_size.y*0.5f;
    m_center.x = m_screen_size.x*0.5f;

    m_snap_threshold_f = true;
    m_snap_threshold_b = false;
}

float CameraSystem::compute_translation_x(){
    return -2.0f * m_center.x / m_screen_size.x;
}

float CameraSystem::compute_translation_y(){
    return 2.0f * m_center.y / m_screen_size.y;
}