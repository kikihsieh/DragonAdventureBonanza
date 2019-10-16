#ifndef DAB_COLLIDER_HPP
#define DAB_COLLIDER_HPP

#endif //DAB_COLLIDER_HPP

struct Collider {
    enum Collision_Direction {
        NONE,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };
    Collision_Direction colliding;
};