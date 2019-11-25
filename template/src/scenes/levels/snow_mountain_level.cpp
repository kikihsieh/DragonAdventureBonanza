#include "snow_mountain_level.hpp"

SnowMountainLeve::SnowMountainLeve() :
        Level() {
}

void SnowMountainLeve::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    s.drawable->texture->height = 50;
    s.physics->walk_speed = 85;
    s.physics->velocity.x = s.physics->walk_speed;
    m_entities.emplace_back(s);
}

void SnowMountainLeve::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    g.shooting->time = 4000;
    g.drawable->texture->height = 320;
    g.drawable->texture->width = 250;
    m_entities.emplace_back(g);
}

bool SnowMountainLeve::init_player() {
    Player player;
    player.airdash = new AirDash();
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
    
    m_background_music = Mix_LoadWAV(audio_path("snow.wav"));
    //m_salmon_dead_sound = Mix_LoadWAV(audio_path("salmon_dead.wav"));
    //m_salmon_eat_sound = Mix_LoadWAV(audio_path("salmon_eat.wav"));
    
    if (m_background_music == nullptr)
    {
        fprintf(stderr, "Failed to load sounds\n %s\n %s\n %s\n make sure the data directory is present",
                audio_path("snow.wav"));
        return false;
    }
    background_music(m_background_music);
    return true;
}

bool SnowMountainLeve::init() {
    m_airdash_system = new AirDashSystem();
    m_physics_system = new PhysicsSystem(true);
   
    return Level::init();
}




void SnowMountainLeve::background_music(Mix_Chunk* b){
    
    // Playing background music indefinitely
    Mix_PlayChannel(-1,b, -1);
    
    fprintf(stderr, "Loaded music\n");
    
}


