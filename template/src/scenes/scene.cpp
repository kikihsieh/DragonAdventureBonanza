#include <ecs/entities/background.hpp>
#include "scene.hpp"
#include "world.hpp"

Scene::Scene() : m_rendersystem(nullptr), m_inputsystem(nullptr), m_background_music(nullptr) {
}

bool Scene::init() {
    m_inputsystem = new InputSystem();
    m_rendersystem = new RenderSystem();
    Background background(get_bg_texture_path());
    m_entities.insert(m_entities.begin(), background);
    m_rendersystem->init_entity(help);
    m_rendersystem->init_entity(credits);
    draw_level_intro = should_draw_level_intro();
    if (draw_level_intro) {
        level_intro = get_level_intro();
        m_rendersystem->init_entity(level_intro);
    }
    background_music();
    if (m_rendersystem->init(&m_entities, get_tiles(), &m_buttons, &m_lights) && m_inputsystem->init(&m_entities, &m_buttons)) {
        state = LOADED;
        return true;
    }
    return false;
}

// Releases all resources
void Scene::destroy() {
    delete m_inputsystem;
    delete m_rendersystem;
    m_rendersystem = nullptr;
    m_inputsystem = nullptr;

    for (auto &entity: m_entities) {
        entity.destroy();
    }
    for (auto &button: m_buttons) {
        button.destroy();
    }
    m_entities.clear();
    m_buttons.clear();
    m_lights.clear();
    drawHelp = false;
    drawCredits = false;
    draw_level_intro = false;

//    Mix_CloseAudio();
    if (m_background_music) {
        //Mix_PauseMusic();
        Mix_FreeMusic(m_background_music);
        m_background_music = nullptr;
    }
}

void Scene::draw(const mat3& projection) {
    if (state == LOADING) {
        return;
    }

    m_rendersystem->draw_all(projection);

    if (draw_level_intro) {
        m_rendersystem->draw_modal(projection, level_intro);
        if (state == RUNNING)
            state = PAUSED;
    }

    if (drawHelp) {
        state = PAUSED;
        m_rendersystem->draw_modal(projection, help);
    }

    if (drawCredits) {
        state = PAUSED;
        m_rendersystem->draw_modal(projection, credits);
    }
}

bool Scene::is_level() {
    return false;
}

void Scene::draw_loading(const mat3& projection) {
    if (m_rendersystem) {
        m_rendersystem->render_text("LOADING...", projection, {510, 400}, {1.0, 1.0, 1.0}, 2.f);
    }
}

void Scene::update(float elapsed_ms, vec2 screen_size) {
    m_screen_size = screen_size;
    m_rendersystem->update(elapsed_ms);
}

void Scene::on_key(int key, int action) {
    if (state == LOADED) {
        return;
    }

    if ((key == GLFW_KEY_H && action == GLFW_PRESS) || (key == GLFW_KEY_P && action == GLFW_PRESS)){
        World::playSFX(World::KEY_PRESS);
    }
    
    if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
        drawHelp = !drawHelp;
        state = (state == RUNNING) ? PAUSED : RUNNING;
        return;
    }
    
    if (key == GLFW_KEY_P && action == GLFW_RELEASE && !drawHelp) {
        state = (state == RUNNING) ? PAUSED : RUNNING;
        return;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS && draw_level_intro) {
        World::playSFX(World::KEY_PRESS);
    }

    if (key == GLFW_KEY_S && action == GLFW_RELEASE && draw_level_intro) {
        draw_level_intro = false;
        state = (state == RUNNING) ? PAUSED : RUNNING;
    }
    m_inputsystem->on_key_update(key, action);
}

void Scene::on_mouse(int key, int action, double xpos, double ypos) {
    m_inputsystem->on_mouse_update(key, action, xpos, ypos);
}

std::map<int, Tile*>* Scene::get_tiles() {
    return &m_tiles;
}

void Scene::addSceneChangeHandler(std::function<void(void)> callback) {
    m_scene_change_callback = callback;
}

void Scene::loadSceneHandler(std::function<void(Scene_name)> callback){
    load_scene = callback;
}

void Scene::exitGameHandler(std::function<void(void)> callback) {
    exit_game = callback;
}

void Scene::background_music() {
    if(!m_background_music)
        printf("Mix_OpenMUS: %s\n", Mix_GetError());
    // Playing background music indefinitely
    Mix_PlayMusic(m_background_music, -1);
}


