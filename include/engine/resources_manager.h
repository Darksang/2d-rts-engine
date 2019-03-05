/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <map>
#include <string>

#include "engine/shader.h"
#include "engine/texture.h"

class ResourcesManager {
    public:
        static std::map<std::string, Shader> Shaders;
        static std::map<std::string, Texture> Textures;

        static void LoadShader(const GLchar * VertexPath, const GLchar * FragmentPath, std::string Name);
        static Shader GetShader(std::string Name);

        static void LoadTexture(const GLchar * TexturePath, GLboolean Alpha, std::string Name);
        static Texture GetTexture(std::string Name);

        static void ListShaders();
        static void ListTextures();

        static void ClearResources();
    
    private:
        ResourcesManager() { }
};

#endif