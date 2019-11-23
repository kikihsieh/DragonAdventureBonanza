#ifndef DAB_PROPERTIES_HPP
#define DAB_PROPERTIES_HPP

struct Properties {
    enum Type {
        DECORATIVE,     // has no effect, is rendered for decoration
        HEALTH,         // +1 health when collected
        SLIPPERY,       // increases vx by friction % / second
        BOUNCY,         // bounces when colliding from top or bottom
        DAMAGE,         // -1 health when collided with
        GOAL,           // when reached, switches to the next level
        TORCH,          // when collided with player projectile, lights up
        PROJECTILE      // used specifically for projectiles
    };

    // Use this constructor for stationary tile entities
    Properties(Type type) : lit(false) {
        this->type = type;

        if (type == BOUNCY) {
            bounce = 1.4f;
        } else if (type == SLIPPERY) {
            friction = 5.4f;
        } else if (type == PROJECTILE) {
            count = 4;
        }
    }

    float bounce;   // percent of vy obtained during each bounce
    float friction; // percent per second of vx increased per second

    int count; // number of times the projectile bounces before disappearing
    bool lit;

    Type type;
};

#endif //DAB_PROPERTIES_HPP
