#ifndef DAB_PROPERTIES_HPP
#define DAB_PROPERTIES_HPP

struct Properties {
    Properties() : bounce(0.f), friction(1.f) {}
    Properties(float bounce, float friction) : bounce(bounce), friction(friction) {}

    float bounce;
    float friction;
};

#endif //DAB_PROPERTIES_HPP
