//
// Created by arden on 10/14/2019.
//

#include "scene.hpp"
#include "ecs/entities/background.hpp"

Scene::Scene() {
}

Scene::~Scene() {
    // TODO: call delete on the contents of m_entities
    m_entities.clear();
};

bool Scene::init() {
    Background background(get_bg_texture_path());
    m_entities.emplace_back(background);

    return m_rendersystem.init(m_entities);
}

// Releases all graphics resources
void Scene::destroy() {
    m_rendersystem.destroy();
    // TODO call delete on the contents of m_entities
    m_entities.clear();
}

void Scene::draw(const mat3& projection) {
    m_rendersystem.draw();
}

bool Scene::is_level() {
    return false;
}

void Scene::update(float elapsed_ms) {

}
