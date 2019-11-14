#include "cave_level.hpp"

CaveLevel::CaveLevel(bool unlocked) :
    Level(unlocked) {
}

bool CaveLevel::init_walking_enemy(int type, vec2 initial_pos) {
    return true;
}


