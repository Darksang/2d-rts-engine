#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
    public:
        Camera2D(float ScreenWidth, float ScreenHeight, float Scale);

        // Position of the camera
        glm::vec2 Position;
        // Zoom of the camera
        float Zoom;
        float MinimumZoom;
        float MaximumZoom;

        void Translate(const glm::vec2 & Translation);
        void LookAt(const glm::vec2 & Point);
        void ZoomIn(float Zoom);
        void ZoomOut(float Zoom);

        glm::vec2 ScreenToWorld(const glm::vec2 & Point);

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix() { return ProjectionMatrix; }

    private:
        void ClampZoom(float Value);

        float ViewportWidth, ViewportHeight;
        float ScaleFactor;
        
        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
};

#endif