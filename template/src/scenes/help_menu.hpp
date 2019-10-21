//
// Created by arden on 10/15/2019.
//

#ifndef DAB_HELP_MENU_H
#define DAB_HELP_MENU_H

#include <memory>

#include "scene.hpp"

class HelpMenu : public Scene {
public:
    HelpMenu();
    ~HelpMenu();

    bool init() override;
    void destroy() override;
    void update(float elapsed_ms) override;
    bool is_forward() override;
    vec2 get_player_position() override;

    const char * get_bg_texture_path() override {
        return textures_path("help_menu.png");
    }
};

#endif //DAB_HELP_MENU_H
