#include "camera2d.h"

Camera2D::Camera2D(int ScreenWidth, int ScreenHeight) : Position(0.0f, 0.0f), ViewMatrix(1.0f), Scale(1.0f), HasToUpdate(true) {
    Width = ScreenWidth;
    Height = ScreenHeight;
}

void Camera2D::Update() {
    if (HasToUpdate) {
        glm::vec2 MidScreen = glm::vec2(Width * 0.5f, Height * 0.5f);
        
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-Position.x + (Width * 0.5f), -Position.y + (Height * 0.5f), 0.0f));

        //ViewMatrix = glm::translate(ViewMatrix, glm::vec3(MidScreen, 0.0f));
        //ViewMatrix = glm::scale(ViewMatrix, glm::vec3(Scale, Scale, 0.0f));
        //ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-MidScreen, 0.0f));

        HasToUpdate = false;
    }
}