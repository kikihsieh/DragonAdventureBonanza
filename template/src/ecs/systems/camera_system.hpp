#pragma once

#include "../entities/player.hpp"

class CameraSystem{
public:
    CameraSystem();
    ~CameraSystem();
    
    bool init(vec2 dim);
    void update(vec2 player_pos, bool moving_forwards);
    void reset();

    float compute_translation_x();
    
private:
    vec2 m_center;
    vec2 m_dim;

    float m_offset_x; // the default amount the camera center is offset from the player

    float m_snap_speed;
    float m_snap_dist; // when player exceeds this distance from the camera center, camera will snap to default position

    bool m_snap_threshold_b; // true if camera should snap to default backwards position
    bool m_snap_threshold_f; // true if camera should snap to default forwards position
};