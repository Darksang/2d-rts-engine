#include "engine/sprite_renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "engine/engine.h"

SpriteRenderer::SpriteRenderer(Shader SpriteShader, Camera2D * Camera) : SpriteShader(SpriteShader), Camera(Camera) {
    Initialize();
}

void SpriteRenderer::Draw(Sprite & S) {
    SpriteShader.Use();

    float Factor = Engine::SCALE_FACTOR;

    // Create Model Matrix
    glm::mat4 Model = glm::mat4(1.0f);
    // Translate sprite based on its center
    glm::vec2 SpriteCenter = glm::vec2(S.Transform.Position.x - (S.SpriteTexture.Width * Factor) / 2.0f, S.Transform.Position.y - (S.SpriteTexture.Height * Factor) / 2.0f);
    Model = glm::translate(Model, glm::vec3(SpriteCenter, 0.0f));

    // Apply rotation from sprite's center instead of top left
    Model = glm::translate(Model, glm::vec3((S.SpriteTexture.Width * Factor) * 0.5f, (S.SpriteTexture.Height * Factor) * 0.5f, 0.0f));
    Model = glm::rotate(Model, glm::radians(S.Transform.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    Model = glm::translate(Model, glm::vec3((S.SpriteTexture.Width * Factor) * -0.5f, (S.SpriteTexture.Height * Factor) * -0.5f, 0.0f));

    // Scale
    Model = glm::scale(Model, glm::vec3((S.SpriteTexture.Width * Factor) * S.Transform.Scale.x, (S.SpriteTexture.Height * Factor) * S.Transform.Scale.y, 1.0f));

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