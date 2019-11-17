#pragma once

#include "../entities/player.hpp"

class CameraSystem{
public:
    CameraSystem();
    ~CameraSystem();
    
    bool init(vec2 level_dim, vec2 screen_size, bool vertical_enabled);
    void update(float elapsed_ms, Player* player, vec2 screen_size);
    void update_x(float elapsed_ms, Player* player, vec2 screen_size);
    void update_y(float elapsed_ms, Player* player, vec2 screen_size);

    float compute_translation_x(vec2 screen_size);
    float compute_translation_y(vec2 screen_size);
    vec2 get_center() { return m_center; };

private:
    vec2 m_center;

    float m_offset_x; // the default amount the camera center is offset from the player

    float m_horizontal_snap_speed;
    float m_vertical_snap_speed;
    float m_horizontal_snap_dist; // when player exceeds this distance from the camera center, camera will snap to default position
    float m_vertical_snap_dist;
    float m_target_y_pos;

    bool m_snap_threshold_b; // true if camera should snap to default backwards position
    bool m_snap_threshold_f; // true if camera should snap to default forwards position

    vec2 m_level_dim;
    bool m_vertical_enabled;
};