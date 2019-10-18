//
// Created by arden on 10/14/2019.
//

#include "scene.hpp"
#include "ecs/entities/background.hpp"

Scene::Scene() {
}

Scene::~Scene() {
    destroy();
};

bool Scene::init() {
    Background background(get_bg_texture_path());
    m_entities.insert(m_entities.begin(), background);

    return m_rendersystem.init(&m_entities) && m_inputsystem->init(&m_entities);
}

// Releases all graphics resources
void Scene::destroy() {
    m_rendersystem.destroy();
    // TODO call delete on the contents of m_entities
    m_entities.clear();
}

void Scene::draw(const mat3& projection) {
    m_rendersystem.draw(projection);
}

bool Scene::is_level() {
    return false;
}

void Scene::update(float elapsed_ms, std::map<const char*, bool> *input_updates) {
    m_inputsystem->update(input_updates);
}
