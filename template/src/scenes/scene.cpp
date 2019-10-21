#include "scene.hpp"
#include "ecs/entities/background.hpp"

Scene::Scene() {
}

bool Scene::init() {
    m_inputsystem = new InputSystem();
    Background background(get_bg_texture_path());
    m_entities.insert(m_entities.begin(), background);
    return m_rendersystem.init(&m_entities) && m_inputsystem->init(&m_entities);
}

// Releases all graphics resources
void Scene::destroy() {
    delete m_inputsystem;
    m_rendersystem.destroy();
    for (auto &entity: m_entities) {
        entity.destroy();
    }
    m_entities.clear();
}

void Scene::draw(const mat3& projection) {
    m_rendersystem.draw(projection);
}

bool Scene::is_level() {
    return false;
}

void Scene::update(float elapsed_ms) {
}

void Scene::on_key(int key, int action) {
    m_inputsystem->on_key_update(key, action);
}

void Scene::on_mouse(int key, int action, double xpos, double ypos) {
    m_inputsystem ->on_mouse_update(key, action, xpos, ypos);
}