#ifndef DAB_PROPERTIES_HPP
#define DAB_PROPERTIES_HPP

struct Properties {
    Properties() : bounce(0.f), friction(0.f) {}
    Properties(float bounce, float friction) : bounce(bounce), friction(friction), count(4) {}

    float bounce;   // percent of speed obtained during each bounce
    float friction; // percent per second of speed retained, < 0 to lose speed, > 1 to gain speed

    int count; // number of times the projectile bounces before disappearing
};

#endif //DAB_PROPERTIES_HPP
