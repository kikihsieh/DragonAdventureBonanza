#ifndef DAB_VICTORY_H
#define DAB_VICTORY_H

#include "scene.hpp"

class Victory : public Scene {
public:
    Victory();

    bool init() override;

    const char * get_bg_texture_path() override {
        return textures_path("end.png");
    }
};

#endif //DAB_STORYLINE_H
