#ifndef DAB_PROPERTIES_HPP
#define DAB_PROPERTIES_HPP

struct Properties {
    enum Type {
        DECORATION,
        COLLECTIBLE,
        SLIPPERY,
        BOUNCY,
        REGULAR
    };

    Properties(Type type) {
        this->type = type;

        if (type == BOUNCY) {
            bounce = 1.0;
        } else if (type == SLIPPERY) {
            friction = 1.2;
        }
    }

    Properties() : bounce(0.2f), friction(0.f), type(REGULAR) {}
    Properties(float bounce, float friction) : bounce(bounce), friction(friction), count(4) {
    }

    float bounce;   // percent of speed obtained during each bounce
    float friction; // percent per second of speed retained, < 0 to lose speed, > 1 to gain speed

    int count; // number of times the projectile bounces before disappearing
    Type type;
};

#endif //DAB_PROPERTIES_HPP
