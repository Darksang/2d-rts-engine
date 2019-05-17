#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
    public:
        Camera2D(float ScreenWidth, float ScreenHeight);

        // Position of the camera
        glm::vec2 Position;
        // Zoom of the camera
        float Zoom;
        float MinimumZoom;
        float MaximumZoom;

        void Translate(const glm::vec2 & Translation);
        void ZoomIn(float Zoom);
        void ZoomOut(float Zoom);

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix() { return ProjectionMatrix; }

    private:
        void ClampZoom(float Value);

        float ViewportWidth, ViewportHeight;
        
        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
};

#endif