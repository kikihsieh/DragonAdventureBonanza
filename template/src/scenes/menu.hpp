//
// Created by arden on 10/15/2019.
//

#include "scene.hpp"

class Menu : public Scene {
public:
    Menu();
    ~Menu();

    const char * get_bg_texture_path() override {
        return textures_path("night.png");
    }
};


