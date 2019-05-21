#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
    public:
        GLuint ID;

        Shader() { ID = 0; }
        Shader(const std::string & VertexPath, const std::string & FragmentPath);
        
        void Use();

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
        void Compile(const char * VertexSource, const char * FragmentSource);
        void CheckShaderErrors(GLuint Shader, const std::string Type);
};

#endif