/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#include "engine/resources_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

std::map<std::string, Shader> ResourcesManager::Shaders;
std::map<std::string, Texture> ResourcesManager::Textures;

void ResourcesManager::LoadShader(const GLchar * VertexPath, const GLchar * FragmentPath, std::string Name) {
    std::string VertexSource, FragmentSource;

    try {
        std::ifstream VertexShaderFile(VertexPath);
        std::ifstream FragmentShaderFile(FragmentPath);

        std::stringstream VertexStream, FragmentStream;

        VertexStream << VertexShaderFile.rdbuf();
        FragmentStream << FragmentShaderFile.rdbuf();

        VertexShaderFile.close();
        FragmentShaderFile.close();

        VertexSource = VertexStream.str();
        FragmentSource = FragmentStream.str();
    } catch (std::exception e) {
        std::cout << "ERROR::SHADER Failed to read shader files" << std::endl;
    }

    const GLchar * VertexShaderSource = VertexSource.c_str();
    const GLchar * FragmentShaderSource = FragmentSource.c_str();

    Shader NewShader;
    NewShader.Compile(VertexShaderSource, FragmentShaderSource);

    Shaders[Name] = NewShader;
}

Shader ResourcesManager::GetShader(std::string Name) {
    return Shaders[Name];
}

void ResourcesManager::LoadTexture(const GLchar * TexturePath, GLboolean Alpha, std::string Name) {
    Texture NewTexture;
    
    if (Alpha) {
        NewTexture.InternalFormat = GL_RGBA;
        NewTexture.Format = GL_RGBA;
    }

    int Width, Height, Channels;
    unsigned char * Data = stbi_load(TexturePath, &Width, &Height, &Channels, 0);

    NewTexture.Load(Width, Height, Data);

    stbi_image_free(Data);

    Textures[Name] = NewTexture;
}

Texture ResourcesManager::GetTexture(std::string Name) {
    return Textures[Name];
}

void ResourcesManager::ListShaders() {
    std::cout << "## LOADED SHADERS ##" << std::endl;

    for (auto Iterator: Shaders)
        std::cout << Iterator.first << std::endl;

    std::cout << "###########################" << std::endl;
}

void ResourcesManager::ListTextures() {
    std::cout << "## LOADED TEXTURES ##" << std::endl;
    
    for (auto Iterator: Textures)
        std::cout << Iterator.first << std::endl;

    std::cout << "###########################" << std::endl;
}

void ResourcesManager::ClearResources() {
    for (auto Iterator: Shaders)
        glDeleteProgram(Iterator.second.ID);
    
    for (auto Iterator: Textures)
        glDeleteTextures(1, &Iterator.second.ID);
}