#include <ecs/entities/background.hpp>
#include "scene.hpp"

Scene::Scene() : m_rendersystem(nullptr), m_inputsystem(nullptr) {
}

bool Scene::init() {
    m_inputsystem = new InputSystem();
    m_rendersystem = new RenderSystem();
    Background background(get_bg_texture_path());
    m_entities.insert(m_entities.begin(), background);
    m_rendersystem->initEntity(help);
    return m_rendersystem->init(&m_entities) && m_inputsystem->init(&m_entities);
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
    drawHelp = false;
}

void Scene::draw(const mat3& projection) {
    m_rendersystem->draw(projection);
    if (drawHelp) {
        m_rendersystem->drawModal(projection, help);
    }
}

bool Scene::is_level() {
    return false;
}

void Scene::update(float elapsed_ms, vec2 screen_size) {
    m_rendersystem->update(elapsed_ms);
}

void Scene::on_key(int key, int action) {
    m_inputsystem->on_key_update(key, action);
}

void Scene::on_mouse(int key, int action, double xpos, double ypos) {
    m_inputsystem ->on_mouse_update(key, action, xpos, ypos);
}
