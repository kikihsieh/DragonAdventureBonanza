#pragma once

#include "scene.hpp"

class LevelSelect : public Scene {
public:
    LevelSelect();

    bool init() override;

    const char * get_bg_texture_path() override {
        return textures_path("level-select/level-select-page.png");
    }
};


