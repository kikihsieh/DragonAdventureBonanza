#include <ecs/systems/default_physics_system.hpp>
#include "cave_level.hpp"

CaveLevel::CaveLevel() :
    Level() {
}

void CaveLevel::init_walking_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Spider s(texture, pos);
    s.animatable->num_columns = 10;
    s.scale = {0.7f, 0.7f};
    m_entities.emplace_back(s);
}

void CaveLevel::init_throwing_enemy(std::shared_ptr<Texture> texture, vec2 pos) {
    Glob g(texture, pos);
    g.animatable->num_columns = 10;
    g.shooting->time = 6000;
    g.scale = {0.15f, 0.15f};
    m_entities.emplace_back(g);
}

bool CaveLevel::init_player() {
    Player player;
    m_entities.emplace_back(player);
    m_player = &m_entities.back();
    return true;
}

bool CaveLevel::init() {
    m_background_music = Mix_LoadMUS(audio_path("cave.wav"));
    Mix_VolumeMusic(MIX_MAX_VOLUME/5);
    m_physics_system = new DefaultPhysicsSystem(true);
    m_intro_modal = new Modal(textures_path("modals/cave.png"));
    Entity dark = Entity();
    dark.drawable = new Drawable();
    dark.is_background = true;
    dark.clipped = false;
    dark.useDepth = false;
    dark.depth = -0.8f;
    dark.drawable->texture_path = textures_path("cave/background.png");
    dark.drawable->fs_shader = shader_path("cave.fs.glsl");
    dark.drawable->vs_shader = shader_path("cave.vs.glsl");
    m_entities.emplace_back(dark);
    bool result = Level::init();
    Entity sec = *std::next(m_entities.begin());
    m_entities.erase(std::next(m_entities.begin()));
    m_entities.emplace_back(sec);

    m_collision_system->set_torches_to_light(5);
    offset = 60.f;

    return result;
}

void CaveLevel::draw(const mat3& projection) {
    Scene::draw(projection);
    
    vec2 camera_center = m_camera_system->get_center();

    std::string string = (m_collision_system->m_torches_to_light > 0) ? "TORCHES TO LIGHT: " + std::to_string((int) fmax(m_collision_system->m_torches_to_light, 0)) : "FIND THE EXIT!";
    m_rendersystem->render_text(string, projection, {camera_center.x-offset, camera_center.y - 375}, {1.0,0.8,0});
}
