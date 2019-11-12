#include "snow_mountain_level.hpp"

SnowMountainLeve::SnowMountainLeve(bool unlocked) :
        Level(unlocked) {
}

bool SnowMountainLeve::init_walking_enemy(int type, vec2 initial_pos) {
    return true;
}
