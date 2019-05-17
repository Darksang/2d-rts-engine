#include "engine/sprite_renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"

SpriteRenderer::SpriteRenderer(Shader SpriteShader, Camera2D * Camera) : SpriteShader(SpriteShader), Camera(Camera) {
    Initialize();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::Draw(Sprite S) {
    SpriteShader.Use();

    // Create Model Matrix
    glm::mat4 Model = glm::mat4(1.0f);
    glm::vec2 Center = glm::vec2(S.Transform.Position.x - S.SpriteTexture.Width / 2.0f, S.Transform.Position.y - S.SpriteTexture.Height / 2.0f);
    Model = glm::translate(Model, glm::vec3(Center, 0.0f));
    Model = glm::scale(Model, glm::vec3(S.SpriteTexture.Width, S.SpriteTexture.Height, 1.0f));

    /*{
        ImGui::Begin("Test");
        ImGui::Text("Position X: %f", S.Transform.Position.x);
        ImGui::Text("Position Y: %f", S.Transform.Position.y);
        ImGui::Text("Texture Width: %i", S.SpriteTexture.Width);
        ImGui::Text("Texture Height: %i", S.SpriteTexture.Height);
        ImGui::BulletText("Model Matrix");
        ImGui::Text("%f %f %f %f", Model[0][0], Model[1][0], Model[2][0], Model[3][0]);
        ImGui::Text("%f %f %f %f", Model[0][1], Model[1][1], Model[2][1], Model[3][1]);
        ImGui::Text("%f %f %f %f", Model[0][2], Model[1][2], Model[2][2], Model[3][2]);
        ImGui::Text("%f %f %f %f", Model[0][3], Model[1][3], Model[2][3], Model[3][3]);
        ImGui::BulletText("View Matrix");
        ImGui::Text("%f %f %f %f", Camera->GetViewMatrix()[0][0], Camera->GetViewMatrix()[1][0], Camera->GetViewMatrix()[2][0], Camera->GetViewMatrix()[3][0]);
        ImGui::Text("%f %f %f %f", Camera->GetViewMatrix()[0][1], Camera->GetViewMatrix()[1][1], Camera->GetViewMatrix()[2][1], Camera->GetViewMatrix()[3][1]);
        ImGui::Text("%f %f %f %f", Camera->GetViewMatrix()[0][2], Camera->GetViewMatrix()[1][2], Camera->GetViewMatrix()[2][2], Camera->GetViewMatrix()[3][2]);
        ImGui::Text("%f %f %f %f", Camera->GetViewMatrix()[0][3], Camera->GetViewMatrix()[1][3], Camera->GetViewMatrix()[2][3], Camera->GetViewMatrix()[3][3]);
        ImGui::BulletText("Projection Matrix");
        ImGui::Text("%f %f %f %f", Camera->GetProjectionMatrix()[0][0], Camera->GetProjectionMatrix()[1][0], Camera->GetProjectionMatrix()[2][0], Camera->GetProjectionMatrix()[3][0]);
        ImGui::Text("%f %f %f %f", Camera->GetProjectionMatrix()[0][1], Camera->GetProjectionMatrix()[1][1], Camera->GetProjectionMatrix()[2][1], Camera->GetProjectionMatrix()[3][1]);
        ImGui::Text("%f %f %f %f", Camera->GetProjectionMatrix()[0][2], Camera->GetProjectionMatrix()[1][2], Camera->GetProjectionMatrix()[2][2], Camera->GetProjectionMatrix()[3][2]);
        ImGui::Text("%f %f %f %f", Camera->GetProjectionMatrix()[0][3], Camera->GetProjectionMatrix()[1][3], Camera->GetProjectionMatrix()[2][3], Camera->GetProjectionMatrix()[3][3]);
        ImGui::End();
    }*/

    SpriteShader.SetMat4("ModelMatrix", Model);
    SpriteShader.SetMat4("ViewMatrix", Camera->GetViewMatrix());

    glActiveTexture(GL_TEXTURE0);
    S.SpriteTexture.Bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::Initialize() {
    GLuint VBO;

    GLfloat Vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
   };

    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Configure Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // Configure Vertex Array Object
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid *)0);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Send uniforms to shader
    SpriteShader.Use();
    SpriteShader.SetInt("Sprite", 0);
    SpriteShader.SetMat4("ProjectionMatrix", Camera->GetProjectionMatrix());
}