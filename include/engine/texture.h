#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>

class Texture {
    public:
        GLuint ID;

        int Width, Height;
        GLuint InternalFormat, Format;

        Texture() : ID(0), Width(0), Height(0), InternalFormat(0), Format(0) { }
        Texture(const std::string & TexturePath, bool Alpha);

        void Bind();
};

#endif