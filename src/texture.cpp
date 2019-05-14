#include "texture.h"

#include "stb_image.h"

Texture::Texture(const std::string & TexturePath, bool Alpha) {
    glGenTextures(1, &this->ID);

    if (!Alpha) {
        InternalFormat = GL_RGB;
        Format = GL_RGB;
    } else {
        InternalFormat  = GL_RGBA;
        Format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int Channels;

    unsigned char * Data = stbi_load(TexturePath.c_str(), &Width, &Height, &Channels, 0);

    if (Data) {
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
   }

   stbi_image_free(Data);

   glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}