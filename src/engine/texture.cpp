#include "engine/texture.h"

Texture::Texture() {
    glGenTextures(1, &this->ID);

    Width = 0;
    Height = 0;

    InternalFormat = GL_RGB;
    Format = GL_RGB;
}

void Texture::Load(GLuint Width, GLuint Height, unsigned char * Data) {
    this->Width = Width;
    this->Height = Height;

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, this->Width, this->Height, 0, this->Format, GL_UNSIGNED_BYTE, Data);

    // Texture filters, by now can only be changed here
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Activate() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}