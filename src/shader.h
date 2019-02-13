#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct shader {
    unsigned int ID;  
};

shader BuildShader(const GLchar * VertexPath, const GLchar * FragmentPath);

// Uniform functions
void UseShader(shader Shader);
void SetBool(shader Shader, const std::string & Name, bool Value);
void SetInt(shader Shader, const std::string & Name, int Value);
void SetFloat(shader Shader, const std::string & Name, float Value);
void SetVec2(shader Shader, const std::string & Name, const glm::vec2 & Vector);
void SetVec2(shader Shader, const std::string & Name, float x, float y);
void SetVec3(shader Shader, const std::string & Name, const glm::vec3 & Vector);
void SetVec3(shader Shader, const std::string & Name, float x, float y, float z);
void SetVec4(shader Shader, const std::string & Name, const glm::vec4 & Vector);
void SetVec4(shader Shader, const std::string & Name, float x, float y, float z, float w);
void SetMat2(shader Shader, const std::string & Name, const glm::mat2 & Matrix);
void SetMat3(shader Shader, const std::string & Name, const glm::mat3 & Matrix);
void SetMat4(shader Shader, const std::string & Name, const glm::mat4 & Matrix);

// Check compile and link errors
void CheckShaderErrors(GLuint Shader, std::string Type);

#endif