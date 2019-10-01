#ifndef DAB_CAMERA_HPP
#define DAB_CAMERA_HPP


#include "common.hpp"
#include "player.hpp"

class Camera {

public:
    void init(vec2 dim);

    void update(vec2 player, bool moving_forwards);
    float compute_translation_x();

private:
    vec2 m_center;
    vec2 m_dim;

    float m_offset_x; // by default amount the camera center is offset from the player

    float m_snap_speed;
};


#endif //DAB_CAMERA_HPP
