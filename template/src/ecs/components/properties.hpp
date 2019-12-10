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
        TORCH_LIT,
        PROJECTILE      // used specifically for projectiles
    };

    // Use this constructor for stationary tile entities
    Properties(Type type) : lit(false) {
        this->type = type;

        if (type == BOUNCY) {
            bounce = 1.4f;
        } else if (type == SLIPPERY) {
            friction = 100.f;
        } else if (type == PROJECTILE) {
            count = 4;
        } else if (type == TORCH_LIT) {
            lit = true;
        }
    }

    float bounce;   // percent of vy obtained during each bounce
    float friction; // percent per second of vx increased per second

    int count; // number of times the projectile bounces before disappearing
    bool lit;
//    float flicker_time = 1000.f; // time in ms before frame should be switched
    float countdown = 0;
    Type type;
};

#endif //DAB_PROPERTIES_HPP
