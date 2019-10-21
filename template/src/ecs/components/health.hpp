#ifndef DAB_HEALTH_HPP
#define DAB_HEALTH_HPP

struct Health {

    Health() :
        health(1) {
    }

    void decrease_health() {
        health--;
    }

    int health;
};

#endif //DAB_HEALTH_HPP
