#include "cave_level.hpp"

CaveLevel::CaveLevel() :
    Level() {
}

void CaveLevel::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    m_entities.emplace_back(s);
}

void CaveLevel::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    m_entities.emplace_back(g);
}

bool CaveLevel::init_player() {
    Player player;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
        return false;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");
        return false;
    }

    return true;
}

bool CaveLevel::init() {
    m_physics_system = new PhysicsSystem(true);
    m_background_music = Mix_LoadWAV(audio_path("cave.wav"));
    return Level::init();
}
