#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
        unsigned int ID;

        Shader(const GLchar * VertexPath, const GLchar * FragmentPath);

        void Activate();
        void SetBool(const std::string & Name, bool Value) const;
        void SetInt(const std::string & Name, int Value) const;
        void SetFloat(const std::string & Name, float Value) const;
        void SetVec2(const std::string & Name, const glm::vec2 & Vector) const;
        void SetVec2(const std::string & Name, float x, float y) const;
        void SetVec3(const std::string & Name, const glm::vec3 & Vector) const;
        void SetVec3(const std::string & Name, float x, float y, float z) const;
        void SetVec4(const std::string & Name, const glm::vec4 & Vector) const;
        void SetVec4(const std::string & Name, float x, float y, float z, float w) const;
        void SetMat2(const std::string & Name, const glm::mat2 & Matrix) const;
        void SetMat3(const std::string & Name, const glm::mat3 & Matrix) const;
        void SetMat4(const std::string & Name, const glm::mat4 & Matrix) const;

    private:
        void CheckShaderErrors(GLuint Shader, const std::string Type);
};

#endif