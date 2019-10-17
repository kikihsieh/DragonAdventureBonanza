//
// Created by arden on 10/14/2019.
//

#include "scene.hpp"
#include "background.hpp"

#include <iostream>
#include <math.h>

Scene::Scene() {
}

Scene::~Scene() = default;

bool Scene::init() {
    m_entities.clear();
    Background background;
    background.scale = {1.f, 1.f};
    background.radians = 0.f;
    m_entities.emplace_back(background);

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
