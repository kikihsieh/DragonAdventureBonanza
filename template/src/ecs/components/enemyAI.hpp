#pragma once

struct EnemyAI
{
    EnemyAI() :
    
            do_left(false),
            do_right(false),
            do_up(false),
            do_down(false),
            do_airdash(false) {
    }
    
    bool do_left;
    bool do_right;
    bool do_up;
    bool do_down;
    bool do_airdash;
};

