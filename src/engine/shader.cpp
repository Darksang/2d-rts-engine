#include "engine/shader.h"

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string & VertexPath, const std::string & FragmentPath) {
    std::string VertexCode, FragmentCode;

    std::ifstream VertexFile(VertexPath);
    std::ifstream FragmentFile(FragmentPath);

    std::stringstream Buffer;

    // Read Vertex File
    Buffer << VertexFile.rdbuf();
    VertexCode = Buffer.str();

    // Read Fragment File
    Buffer.str(std::string());
    Buffer << FragmentFile.rdbuf();
    FragmentCode = Buffer.str();

    VertexFile.close();
    FragmentFile.close();

    Compile(VertexCode.c_str(), FragmentCode.c_str());
}

void Shader::Use() {
    glUseProgram(ID);
}

void Shader::SetBool(const std::string & Name, bool Value) const {
    glUniform1i(glGetUniformLocation(ID, Name.c_str()), Value);
}

void Shader::SetInt(const std::string & Name, int Value) const {
    glUniform1i(glGetUniformLocation(ID, Name.c_str()), Value);
}

void Shader::SetFloat(const std::string & Name, float Value) const {
    glUniform1f(glGetUniformLocation(ID, Name.c_str()), Value);
}

void Shader::SetVec2(const std::string & Name, const glm::vec2 & Vector) const {
    glUniform2fv(glGetUniformLocation(ID, Name.c_str()), 1, &Vector[0]);
}

void Shader::SetVec2(const std::string & Name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, Name.c_str()), x, y);
}

void Shader::SetVec3(const std::string & Name, const glm::vec3 & Vector) const {
    glUniform3fv(glGetUniformLocation(ID, Name.c_str()), 1, &Vector[0]);
}

void Shader::SetVec3(const std::string & Name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, Name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string & Name, const glm::vec4 & Vector) const {
    glUniform4fv(glGetUniformLocation(ID, Name.c_str()), 1, &Vector[0]);
}

void Shader::SetVec4(const std::string & Name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, Name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string & Name, const glm::mat2 & Matrix) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, Name.c_str()), 1, GL_FALSE, &Matrix[0][0]);
}

void Shader::SetMat3(const std::string & Name, const glm::mat3 & Matrix) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, Name.c_str()), 1, GL_FALSE, &Matrix[0][0]);
}

void Shader::SetMat4(const std::string & Name, const glm::mat4 & Matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, Name.c_str()), 1, GL_FALSE, &Matrix[0][0]);
}

void Shader::Compile(const char * VertexSource, const char * FragmentSource) {
    // Compile Vertex Shader
    GLuint Vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Vertex, 1, &VertexSource, 0);
    glCompileShader(Vertex);
    CheckShaderErrors(Vertex, "VERTEX SHADER");

    // Compile Fragment Shader
    GLuint Fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Fragment, 1, &FragmentSource, 0);
    glCompileShader(Fragment);
    CheckShaderErrors(Fragment, "FRAGMENT SHADER");

    // Link Program
    ID = glCreateProgram();
    glAttachShader(ID, Vertex);
    glAttachShader(ID, Fragment);
    glLinkProgram(ID);
    CheckShaderErrors(ID, "LINK");

    glDeleteShader(Vertex);
    glDeleteShader(Fragment);
}

void Shader::CheckShaderErrors(GLuint Shader, std::string Type) {
    GLint Success;
    GLchar InfoLog[1024];

    if (Type != "LINK") {
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
        if (!Success) {
            glGetShaderInfoLog(Shader, 1024, NULL, InfoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR in " << Type << "\n" << InfoLog << "\n---------\n" << std::endl;
        }
    } else {
        glGetProgramiv(Shader, GL_LINK_STATUS, &Success);
        if (!Success) {
            glGetProgramInfoLog(Shader, 1024, NULL, InfoLog);
            std::cout << "ERROR::SHADER_PROGRAM_LINKING_ERROR" << "\n" << InfoLog << "\n---------\n" << std::endl;
        }
    }
}