#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include <glm/glm.hpp>

struct Transform2D {
    glm::vec2 Position;
    glm::vec2 Scale;
    float Rotation;

    Transform2D() : Position(0.0f), Scale(1.0f), Rotation(0.0f) { }
};

#endif