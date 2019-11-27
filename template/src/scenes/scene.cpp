#include <ecs/entities/background.hpp>
#include "scene.hpp"

Scene::Scene() : m_rendersystem(nullptr), m_inputsystem(nullptr) {
}


bool Scene::init() {
    m_inputsystem = new InputSystem();
    m_rendersystem = new RenderSystem();
    Background background(get_bg_texture_path());
    m_entities.insert(m_entities.begin(), background);
    m_rendersystem->init_entity(help);
    if (m_rendersystem->init(&m_entities, get_tiles()) && m_inputsystem->init(&m_entities, &m_buttons)) {
        state = LOADED;
        return true;
    }
    return false;
    

}

// Releases all graphics resources
void Scene::destroy() {
    delete m_inputsystem;
    delete m_rendersystem;
    m_rendersystem = nullptr;
    m_inputsystem = nullptr;
    for (auto &entity: m_entities) {
        entity.destroy();
    }
    m_entities.clear();
    m_buttons.clear();
    drawHelp = false;
   
    if (m_background_music != nullptr){
        Mix_FreeChunk(m_background_music);
        m_background_music = nullptr;
    }
    Mix_CloseAudio();
}

void Scene::draw(const mat3& projection) {
    if (state == LOADING) {
        // TODO: draw loading screen
        return;
    }
    m_rendersystem->draw_all(projection);
    if (drawHelp) {
        state = PAUSED;
        m_rendersystem->draw_modal(projection, help);
    }
}

bool Scene::is_level() {
    return false;
}

void Scene::update(float elapsed_ms, vec2 screen_size) {
    m_rendersystem->update(elapsed_ms);
}

void Scene::on_key(int key, int action) {
    if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
        drawHelp = !drawHelp;
        state = (state == RUNNING) ? PAUSED : RUNNING;
        return;
    }
    if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
        if (!drawHelp)
            state = (state == RUNNING) ? PAUSED : RUNNING;
        return;
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


void Scene::background_music(Mix_Chunk* b){

    // Playing background music indefinitely
    Mix_PlayChannel(-1,b, -1);

    fprintf(stderr, "Loaded music\n");

}


