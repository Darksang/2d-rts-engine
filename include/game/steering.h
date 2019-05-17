#ifndef STEERING_H
#define STEERING_H

#include "glm/glm.hpp"

class Steering {
    public:
        glm::vec2 Velocity;
        float Rotation;

        Steering() {
            Velocity = glm::vec2(0.0f, 0.0f);
            Rotation = 0.0f;
        }
};

#endif