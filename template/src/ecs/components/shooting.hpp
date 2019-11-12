#pragma once

struct Shooting
{
    Shooting() :
        time(20) {
    }
    float m_next_projectile = 0.f;
    int time;
};

