#ifndef DAB_COLLIDER_HPP
#define DAB_COLLIDER_HPP

struct Collider {

    Collider() :
            horizontal(false),
            top(false),
            bottom(false) {
    }

    void reset() {
        top = false;
        bottom = false;
        horizontal = false;
    }

    bool horizontal;
    bool top;
    bool bottom;
};

#endif //DAB_COLLIDER_HPP
