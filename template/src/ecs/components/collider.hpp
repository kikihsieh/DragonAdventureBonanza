#ifndef DAB_COLLIDER_HPP
#define DAB_COLLIDER_HPP

struct Collider {
    enum Collision_Direction {
        NONE,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };

    Collider() :
        colliding(Collision_Direction::NONE),
        bounce(0.1f) {
    }
    Collision_Direction colliding;

    // value from 0-1 for bounciness of a collision with the object where 0 means it does not bounce
    float bounce;
};

#endif //DAB_COLLIDER_HPP
