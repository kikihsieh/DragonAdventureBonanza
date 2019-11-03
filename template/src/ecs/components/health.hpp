#ifndef DAB_HEALTH_HPP
#define DAB_HEALTH_HPP

#include <common.hpp>

struct Health {

    Health() :
        health(1) {
    }

    void decrease_health() {
        health--;
    }

    int health;
    bool is_player = false;
    vec2 last_safe;

    float update_last_safe_frequency = 100;
    float update_last_safe_timer = 0.f;
};

#endif //DAB_HEALTH_HPP
