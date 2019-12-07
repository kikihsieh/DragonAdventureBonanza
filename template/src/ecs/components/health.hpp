#ifndef DAB_HEALTH_HPP
#define DAB_HEALTH_HPP

#include <common.hpp>
#include <iostream>

struct Health {

    Health() :
        health(1) {
    }

    void decrease_health() {
        health--;
        if (is_player) {
            invincible = true;
        }

        if (health < 0)
            health = 0;
    }

    void increase_health() {
        health++;
    }

    int health;
    bool is_player = false;
    vec2 last_safe;

    bool is_boss = false;

    bool invincible = false;
    float invincible_timer = 0;
    float invincibility_duration = 1000;

    float update_last_safe_frequency = 100;
    float update_last_safe_timer = 0.f;
};

#endif //DAB_HEALTH_HPP
