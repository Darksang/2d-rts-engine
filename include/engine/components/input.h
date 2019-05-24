#ifndef INPUT_H
#define INPUT_H

#include "engine/ecs/ECS.h"

#include "glm/glm.hpp"

struct Input {
    ECS_DECLARE_TYPE;

    Input() : MousePosition(0.0f), MouseWheelDelta(0.0f) { }

    glm::vec2 MousePosition;
    glm::vec2 MouseWheelDelta;
};

ECS_DEFINE_TYPE(Input);

#endif