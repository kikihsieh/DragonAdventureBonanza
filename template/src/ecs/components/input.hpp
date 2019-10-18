#pragma once

struct Input
{
    Input() :
            left(false),
            right(false),
            up(false),
            shift(false) {
    }

    bool left;
    bool right;
    bool up;
    bool shift;
};
