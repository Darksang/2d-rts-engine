#ifndef TEXTURE_H
#define TEXTURE

#include <glad/glad.h>

class Texture {
    public:
        // OpenGL ID for the texture
        GLuint ID;
        // Width and Height of the texture
        GLuint Width, Height;
        // Image format such as RGB or RGBA
        GLuint InternalFormat, Format;

        Texture();

        void Load(GLuint Width, GLuint Height, unsigned char * Data);
        void Activate();
};

#endif