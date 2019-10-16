//
// Created by arden on 10/14/2019.
//

#include "scene.hpp"

#include <iostream>
#include <math.h>

Scene::Scene() {
}

Scene::~Scene() = default;

bool Scene::init(const char* path) {
    return m_background.init(path);
}

// Releases all graphics resources
void Scene::destroy() {
    m_background.destroy();
}

void Scene::draw(const mat3& projection) {
    m_background.draw(projection);
}

bool Scene::is_level() {
    return false;
}

void Scene::update(float elapsed_ms) {

}
