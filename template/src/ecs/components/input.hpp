#pragma once

struct Input
{
    Input(){
        left_pressed = false;
        right_pressed = false;
        up_pressed = false;
        shift_left = false;
        shift_right = false;
    }

    bool left_pressed;
    bool right_pressed;
    bool up_pressed;
    bool shift_right;
    bool shift_left;
    // more for button clicked
};
