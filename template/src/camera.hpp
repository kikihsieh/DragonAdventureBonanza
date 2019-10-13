#ifndef DAB_CAMERA_HPP
#define DAB_CAMERA_HPP

#include "common.hpp"
#include "player.hpp"

class Camera {

public:
    void init(vec2 dim);

    void update(vec2 player, bool moving_forwards);
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

#endif //DAB_CAMERA_HPP
