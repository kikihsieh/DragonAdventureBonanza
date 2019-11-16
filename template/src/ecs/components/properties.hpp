#ifndef DAB_PROPERTIES_HPP
#define DAB_PROPERTIES_HPP

struct Properties {
    enum Type {
        DECORATIVE,     // has no effect, is rendered for decoration
        HEALTH,         // +1 health when collected
        SLIPPERY,       // slippery to stand on
        BOUNCY,         // bounces when colliding from top or bottom
        DAMAGE,         // -1 health when collided with
        PROJECTILE      // used specifically for enemy projectiles
    };

    // Use this constructor for stationary tile entities
    Properties(Type type) {
        this->type = type;

        if (type == BOUNCY) {
            bounce = 1.0;
        } else if (type == SLIPPERY) {
            friction = 1.2;
        } else if (type == PROJECTILE) {
            count = 4;
        }
    }

    float bounce;   // percent of speed obtained during each bounce
    float friction; // percent per second of speed retained, < 0 to lose speed, > 1 to gain speed

    int count; // number of times the projectile bounces before disappearing
    Type type;
};

#endif //DAB_PROPERTIES_HPP
