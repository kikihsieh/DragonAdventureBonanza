//
// Created by arden on 10/14/2019.
//

#include "scene.hpp"
#include "background.hpp"

Scene::Scene() {
}

Scene::~Scene() {
    m_entities.clear();
};

bool Scene::init() {
    Background background;
    background.scale = {1.f, 1.f};
    background.radians = 0.f;
    background.init(get_bg_texture_path());
    m_entities.push_back(background);

    return m_rendersystem.init(m_entities);
}

// Releases all graphics resources
void Scene::destroy() {
    m_rendersystem.destroy();
}

void Scene::draw(const mat3& projection) {
    m_rendersystem.draw();
}

bool Scene::is_level() {
    return false;
}

void Scene::update(float elapsed_ms) {

}
