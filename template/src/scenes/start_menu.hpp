//
// Created by arden on 10/15/2019.
//

#ifndef DAB_START_MENU_H
#define DAB_START_MENU_H

#include <memory>
#include <vector>

#include "scene.hpp"
#include "button.hpp"

class StartMenu : public Scene {
public:
    StartMenu();
    ~StartMenu();

    bool init() override;
    void destroy() override;
    void update(float elapsed_ms, std::map<const char*, bool> *input_updates) override;
    void draw(const mat3& projection) override;

    const char * get_bg_texture_path() override {
        return textures_path("night.png");
    }

private:
    std::vector<std::shared_ptr<Button>> m_buttons;

};


#endif //DAB_START_MENU_H
