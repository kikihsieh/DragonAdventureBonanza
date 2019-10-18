#pragma once
#include <vector>
#include <map>
#include "common.hpp"
#include "../entities/entity.hpp"

class InputSystem{
public:
    bool init(std::vector<Entity>* entities);
    void update(std::map<const char*, bool> *input_updates);

private:
    std::vector<Entity>* m_entities;
};