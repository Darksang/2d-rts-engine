#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum projection_type {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

enum camera_movement {
    FORWARD,
    BACKWARDS,
    LEFT,
    RIGHT
};

struct camera {
    projection_type Projection;

    int FieldOfView; // Value used for perspective projection
    int Size; // Value used for orthographic projection

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
};

camera CreatePerspectiveCamera(glm::vec3 Position, int FieldOfView, float Near, float Far);
camera CreateOrthographicCamera(int Size, float Near, float Far);

glm::mat4 GetViewMatrix(camera Camera);
void CameraUpdateVectors(camera * Camera);

void CameraProcessKeyboard(camera * Camera, camera_movement Direction, float DeltaTime);
void CameraProcessMouseMovement(camera * Camera, float XOffset, float YOffset);

#endif