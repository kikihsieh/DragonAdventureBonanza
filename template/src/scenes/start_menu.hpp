//
// Created by arden on 10/15/2019.
//

#ifndef DAB_START_MENU_H
#define DAB_START_MENU_H

#include <memory>

#include "scene.hpp"

class StartMenu : public Scene {
public:
    StartMenu();

    bool init() override;
    void update(float elapsed_ms) override;

    const char * get_bg_texture_path() override {
        return textures_path("title.png");
    }
};

#endif //DAB_START_MENU_H
