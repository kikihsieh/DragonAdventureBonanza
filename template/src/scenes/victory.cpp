#include "victory.hpp"
#include "world.hpp"

Victory::Victory() {
}

bool Victory::init() {
    
    World::playSFX(World::WOW);
    m_background_music = Mix_LoadMUS(audio_path("victory.wav"));
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Scene::init();
    return true;
   
}
