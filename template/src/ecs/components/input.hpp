#pragma once

struct Input
{
    Input() :
            left(false),
            right(false),
            up(false),
            shift(false),
            mouse_left(false) {
    }

    bool left;
    bool right;
    bool up;
    bool shift;
    bool mouse_left;
};
