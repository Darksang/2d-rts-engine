#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct shader {
    unsigned int ID;  
};

shader BuildShader(const GLchar * VertexPath, const GLchar * FragmentPath);

void UseShader(shader Shader);

#endif