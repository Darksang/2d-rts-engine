#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct Transform {
    glm::vec2 Position;
    glm::vec2 Scale;
    float Rotation;

    Transform() : Position(0.0f), Scale(1.0f), Rotation(0.0f) { }
};

#endif