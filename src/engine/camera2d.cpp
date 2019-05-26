#include "engine/camera2d.h"

Camera2D::Camera2D(float ScreenWidth, float ScreenHeight, float Scale) : Position(0.0f, 0.0f), Zoom(1.0f), ViewMatrix(1.0f), ProjectionMatrix(1.0f) {
    ScaleFactor = Scale;
    ViewportWidth = ScreenWidth * ScaleFactor;
    ViewportHeight = ScreenHeight * ScaleFactor;

    // Left, Right, Top, Bottom
    ProjectionMatrix = glm::ortho(0.0f, ViewportWidth, ViewportHeight, 0.0f);

    MinimumZoom = 0.5f;
    MaximumZoom = 1.5f;
}

void Camera2D::Translate(const glm::vec2 & Translation) {
    Position += Translation;
}

void Camera2D::LookAt(const glm::vec2 & Point) {
    Position = Point;
}

void Camera2D::ZoomIn(float Zoom) {
    ClampZoom(this->Zoom + Zoom);
}

void Camera2D::ZoomOut(float Zoom) {
    ClampZoom(this->Zoom - Zoom);
}

glm::vec2 Camera2D::ScreenToWorld(const glm::vec2 & Point) {
    glm::vec2 Result = glm::inverse(GetViewMatrix()) * glm::vec4(Point.x * ScaleFactor, Point.y * ScaleFactor, 1.0f, 1.0f);
    return glm::vec2(Result.x, Result.y);
}

glm::mat4 Camera2D::GetViewMatrix() {
    ViewMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-Position, 0.0f));
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(ViewportWidth * 0.5f, ViewportHeight * 0.5f, 0.0f));
    ViewMatrix = glm::scale(ViewMatrix, glm::vec3(Zoom, Zoom, 1.0f));

    return ViewMatrix;
}

void Camera2D::UpdateViewport(int Width, int Height) {
    ViewportWidth = static_cast<float>(Width) * ScaleFactor;
    ViewportHeight = static_cast<float>(Height) * ScaleFactor;

    ProjectionMatrix = glm::ortho(0.0f, ViewportWidth, ViewportHeight, 0.0f);
}

void Camera2D::ClampZoom(float Value) {
    if (Value < MinimumZoom)
        Zoom = MinimumZoom;
    else if (Value > MaximumZoom)
        Zoom = MaximumZoom;
    else
        Zoom = Value;
}