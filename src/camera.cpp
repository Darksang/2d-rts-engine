#include "camera.h"

camera CreatePerspectiveCamera(glm::vec3 Position, int FieldOfView, float Near, float Far) {
    camera Camera = {};

    Camera.Projection = PERSPECTIVE;
    Camera.FieldOfView = FieldOfView;
    Camera.Size = 0;
    Camera.NearClippingPlane = Near;
    Camera.FarClippingPlane = Far;

    Camera.Position = Position;
    Camera.Front = glm::vec3(0.0f, 0.0f, -1.0f);
    Camera.Up = glm::vec3(0.0f, 1.0f, 0.0f);
    Camera.WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera.Yaw = -90.0f;
    Camera.Pitch = 0.0f;

    CameraUpdateVectors(&Camera);

    return Camera;
}

// TODO: Finish implementing an orthographic camera
camera CreateOrthographicCamera(int Size, float Near, float Far) {
    camera Camera = {};

    Camera.Projection = ORTHOGRAPHIC;
    Camera.FieldOfView = 0;
    Camera.Size = Size;
    Camera.NearClippingPlane = Near;
    Camera.FarClippingPlane = Far;

    return Camera;
}

glm::mat4 GetViewMatrix(camera Camera) {
    return glm::lookAt(Camera.Position, Camera.Position + Camera.Front, Camera.Up);
}

void CameraUpdateVectors(camera * Camera) {
    // Calculate new Front vector
    glm::vec3 Front;

    Front.x = cos(glm::radians(Camera->Yaw)) * cos(glm::radians(Camera->Pitch));
    Front.y = sin(glm::radians(Camera->Pitch));
    Front.z = sin(glm::radians(Camera->Yaw)) * cos(glm::radians(Camera->Pitch));

    Camera->Front = glm::normalize(Front);

    // Recalculate Right and Up vectors
    Camera->Right = glm::normalize(glm::cross(Camera->Front, Camera->WorldUp));
    Camera->Up = glm::normalize(glm::cross(Camera->Right, Camera->Front));
}

void CameraProcessKeyboard(camera * Camera, camera_movement Direction, float DeltaTime) {
    // TODO: Velocity is hardcoded, allow to change it
    float Velocity = 2.5f * DeltaTime;

    if (Direction == FORWARD)
        Camera->Position += Camera->Front * Velocity;
    if (Direction == BACKWARDS)
        Camera->Position -= Camera->Front * Velocity;
    if (Direction == LEFT)
        Camera->Position -= Camera->Right * Velocity;
    if (Direction == RIGHT)
        Camera->Position += Camera->Right * Velocity;
}

void CameraProcessMouseMovement(camera * Camera, float XOffset, float YOffset) {
    // TODO: Sensitivity is hardcoded, allow to change it
    float Sensitivity = 0.1f;
    XOffset *= Sensitivity;
    YOffset *= Sensitivity;

    Camera->Yaw += XOffset;
    Camera->Pitch += YOffset;

    // Clamp Pitch to screen doesn't get flipped
    if (Camera->Pitch > 89.0f)
        Camera->Pitch = 89.0f;
    if (Camera->Pitch < -89.0f)
        Camera->Pitch = -89.0f;

    CameraUpdateVectors(Camera);
}