#pragma once

struct Shooting
{
    Shooting() :
        time(8000) {
    }
    float m_next_projectile = 0.f;
    int time;
    bool sound = true;
};

