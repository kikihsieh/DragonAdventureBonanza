#ifndef DAB_STORYLINE_H
#define DAB_STORYLINE_H

#include "scene.hpp"

class StoryLine : public Scene {
public:
    StoryLine();

    bool init() override;
    void on_key(int key, int action) override;

    const char * get_bg_texture_path() override {
        return textures_path("intro.png");
    }
};

#endif //DAB_STORYLINE_H
