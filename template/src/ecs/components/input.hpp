#pragma once

struct Input
{
    Input() :
            left(false),
            right(false),
            up(false),
            down(false),
            shift(false),
            space(false),
            mouse_left(false) {
    }

    bool left;
    bool right;
    bool up;
    bool down;
    bool shift;
    bool space;
    bool mouse_left;
};
