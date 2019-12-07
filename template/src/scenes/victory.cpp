#include "victory.hpp"

Victory::Victory() {
}

bool Victory::init() {
    m_background_music = Mix_LoadMUS(audio_path("victory.wav"));
    Scene::init();
    return true;
}