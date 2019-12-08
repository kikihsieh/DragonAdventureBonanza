#include "victory.hpp"

Victory::Victory() {
}

bool Victory::init() {
    m_background_music = Mix_LoadMUS(audio_path("victory.wav"));
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Scene::init();
    return true;
}
