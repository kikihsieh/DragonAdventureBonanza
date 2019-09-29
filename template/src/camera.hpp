#ifndef DAB_CAMERA_HPP
#define DAB_CAMERA_HPP


#include "common.hpp"

class Camera {

public:
    bool init(vec2 dim);

    void update(vec2 player_pos);
    float compute_translation_x();

private:
    vec2 m_center;
    vec2 m_dim;
};


#endif //DAB_CAMERA_HPP
