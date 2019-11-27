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
    
    m_background_music = Mix_LoadWAV(audio_path("cave.wav"));
    //m_salmon_dead_sound = Mix_LoadWAV(audio_path("salmon_dead.wav"));
    //m_salmon_eat_sound = Mix_LoadWAV(audio_path("salmon_eat.wav"));
    
    if (m_background_music == nullptr)
    {
        fprintf(stderr, "Failed to load sounds\n %s\n %s\n %s\n make sure the data directory is present",
                audio_path("cave.wav"));
        return false;
    }
    background_music(m_background_music);
    
    return true;
}

bool CaveLevel::init() {
    m_physics_system = new PhysicsSystem(true);
   
    return Level::init();
}



//void CaveLevel::background_music(Mix_Chunk* b){
//
//    // Playing background music indefinitely
//    Mix_PlayChannel(-1,b, -1);
//
//    fprintf(stderr, "Loaded music\n");
//
//}
