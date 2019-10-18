#ifndef DAB_COLLIDER_HPP
#define DAB_COLLIDER_HPP

struct Collider {

    Collider() :
            horizontal(false),
            vertical(false) {
    }

    void reset() {
        vertical = false;
        horizontal = false;
    }

    bool horizontal;
    bool vertical;
};

#endif //DAB_COLLIDER_HPP
