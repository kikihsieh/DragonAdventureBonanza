#include "volcano_level.hpp"

VolcanoLevel::VolcanoLevel(bool unlocked) :
        Level(unlocked) {
}

bool VolcanoLevel::init_walking_enemy(int type, vec2 initial_pos) {
    return true;
}
