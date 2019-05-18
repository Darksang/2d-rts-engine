#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/sprite.h"
#include "engine/camera2d.h"

class SpriteRenderer {
    public:
        SpriteRenderer(Shader SpriteShader, Camera2D * Camera);

        Shader SpriteShader;

        Camera2D * Camera;

        void Draw(Sprite & S);

    private:
        GLuint VAO;

        void Initialize();
};

#endif