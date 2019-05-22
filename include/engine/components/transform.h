#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "engine/ecs/ECS.h"

#include "glm/glm.hpp"

struct Transform {
    ECS_DECLARE_TYPE;

    Transform() : Position(0.0f), Scale(1.0f), Rotation(0.0f) { }

    glm::vec2 Position;
    glm::vec2 Scale;
    float Rotation;
};

ECS_DEFINE_TYPE(Transform);

#endif