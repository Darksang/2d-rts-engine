#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
    public:
        Camera2D(int ScreenWidth, int ScreenHeight);

        glm::vec2 Position;
        float Scale;

        void Update();

        glm::mat4 GetViewMatrix() { return ViewMatrix; }

    private:
        int Width, Height;
        
        glm::mat4 ViewMatrix;

        bool HasToUpdate;
};

#endif