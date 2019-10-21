#ifndef DAB_COLLIDER_HPP
#define DAB_COLLIDER_HPP

struct Collider {

    Collider() :
            left(false),
            top(false),
            right(false),
            bottom(false) {
    }

    void reset() {
        top = false;
        bottom = false;
        left = false;
        right = false;
    }

    bool right;
    bool left;
    bool top;
    bool bottom;
};

#endif //DAB_COLLIDER_HPP
