#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform {
    public:
        glm::vec2 Position;
        float Rotation;

        Transform() {
            Position = vec2(0.0f);
            Rotation = 0.0f;
        }
};

#endif