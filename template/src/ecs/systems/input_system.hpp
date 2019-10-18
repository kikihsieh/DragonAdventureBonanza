#pragma once

#include <vector>
#include "../entities/entity.hpp"

class InputSystem {
public:
    bool init(std::vector<Entity>* entities);
    void update(int key, int action);

private:
    std::vector<Entity>* m_entities;
};