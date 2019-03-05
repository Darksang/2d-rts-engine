#include "engine/camera.h"

Camera::Camera(glm::vec3 Position, int FOV, float Near, float Far) {
    Projection = PERSPECTIVE;
    FieldOfView = FOV;
    Size = 0;
    NearClippingPlane = Near;
    FarClippingPlane = Far;

    this->Position = Position;
    Front = glm::vec3(0.0f, 0.0f, -1.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    Yaw = -90.0f;
    Pitch = 0.0f;

    UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement Direction, float DeltaTime) {
    // TODO: Velocity is hardcoded, allow to change it
    float Velocity = 2.5f * DeltaTime;

    if (Direction == FORWARD)
        Position += Front * Velocity;
    if (Direction == BACKWARDS)
        Position -= Front * Velocity;
    if (Direction == LEFT)
        Position -= Right * Velocity;
    if (Direction == RIGHT)
        Position += Right * Velocity;
}

void Camera::ProcessMouseMovement(float OffsetX, float OffsetY) {
    // TODO: Sensitivity is hardcoded, allow to change it
    float Sensitivity = 0.1f;
    OffsetX *= Sensitivity;
    OffsetY *= Sensitivity;

    Yaw += OffsetX;
    Pitch += OffsetY;

    // Clamp Pitch to screen doesn't get flipped
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    UpdateVectors();
}

void Camera::UpdateVectors() {
    // Calculate new Front vector
    glm::vec3 NewFront;

    NewFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    NewFront.y = sin(glm::radians(Pitch));
    NewFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(NewFront);

    // Recalculate Right and Up vectors
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}