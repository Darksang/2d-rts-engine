#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum ProjectionType {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

enum CameraMovement {
    FORWARD,
    BACKWARDS,
    LEFT,
    RIGHT
};

class Camera {
    public:
        ProjectionType Projection;

        int FieldOfView; // Value used for perspective projection
        int Size;        // Value used for orthographic projection

        float NearClippingPlane;
        float FarClippingPlane;

        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // Euler angles
        float Yaw;
        float Pitch;

        Camera(glm::vec3 Position, int FOV, float Near, float Far);

        glm::mat4 GetViewMatrix();

        void ProcessKeyboard(CameraMovement Direction, float DeltaTime);
        void ProcessMouseMovement(float OffsetX, float OffsetY);

    private:
        void UpdateVectors();
};

#endif