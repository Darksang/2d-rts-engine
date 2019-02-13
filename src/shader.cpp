#include "shader.h"

shader BuildShader(const GLchar * VertexPath, const GLchar * FragmentPath) {
    shader Result = {};

    // Read programs from specified path
    std::string VertexCode;
    std::string FragmentCode;

    std::ifstream VertexShaderFile;
    std::ifstream FragmentShaderFile;

    VertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    FragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        VertexShaderFile.open(VertexPath);
        FragmentShaderFile.open(FragmentPath);

        std::stringstream VertexShaderStream, FragmentShaderStream;

        VertexShaderStream << VertexShaderFile.rdbuf();
        FragmentShaderStream << FragmentShaderFile.rdbuf();

        VertexShaderFile.close();
        FragmentShaderFile.close();

        VertexCode = VertexShaderStream.str();
        FragmentCode = FragmentShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char * VertexStr = VertexCode.c_str();
    const char * FragmentStr = FragmentCode.c_str();

    // Compile Vertex Shader
    unsigned int Vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(Vertex, 1, &VertexStr, NULL);
    glCompileShader(Vertex);

    CheckShaderErrors(Vertex, "VERTEX SHADER");

    // Compile Fragment Shader
    unsigned int Fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(Fragment, 1, &FragmentStr, NULL);
    glCompileShader(Fragment);

    CheckShaderErrors(Fragment, "FRAGMENT SHADER");

    // Link into shader program
    unsigned int ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, Vertex);
    glAttachShader(ShaderProgram, Fragment);
    glLinkProgram(ShaderProgram);

    CheckShaderErrors(ShaderProgram, "LINK");

    glDeleteShader(Vertex);
    glDeleteShader(Fragment);

    Result.ID = ShaderProgram;

    return Result;
}

void UseShader(shader Shader) {
    glUseProgram(Shader.ID);
}

void SetBool(shader Shader, const std::string & Name, bool Value) {
    glUniform1i(glGetUniformLocation(Shader.ID, Name.c_str()), Value);
}

void SetInt(shader Shader, const std::string & Name, int Value) {
    glUniform1i(glGetUniformLocation(Shader.ID, Name.c_str()), Value);
}

void SetFloat(shader Shader, const std::string & Name, float Value) {
    glUniform1f(glGetUniformLocation(Shader.ID, Name.c_str()), Value);
}

void SetVec2(shader Shader, const std::string & Name, const glm::vec2 & Vector) {
    glUniform2fv(glGetUniformLocation(Shader.ID, Name.c_str()), 1, &Vector[0]);
}

void SetVec2(shader Shader, const std::string & Name, float x, float y) {
    glUniform2f(glGetUniformLocation(Shader.ID, Name.c_str()), x, y);
}

void SetVec3(shader Shader, const std::string & Name, const glm::vec3 & Vector) {
    glUniform3fv(glGetUniformLocation(Shader.ID, Name.c_str()), 1, &Vector[0]);
}

void SetVec3(shader Shader, const std::string & Name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(Shader.ID, Name.c_str()), x, y, z);
}

void SetVec4(shader Shader, const std::string & Name, const glm::vec4 & Vector) {
    glUniform4fv(glGetUniformLocation(Shader.ID, Name.c_str()), 1, &Vector[0]);
}

void SetVec4(shader Shader, const std::string & Name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(Shader.ID, Name.c_str()), x, y, z, w);
}

void SetMat2(shader Shader, const std::string & Name, const glm::mat2 & Matrix) {
    glUniformMatrix2fv(glGetUniformLocation(Shader.ID, Name.c_str()), 1, GL_FALSE, &Matrix[0][0]);
}

void SetMat3(shader Shader, const std::string & Name, const glm::mat3 & Matrix) {
    glUniformMatrix3fv(glGetUniformLocation(Shader.ID, Name.c_str()), 1, GL_FALSE, &Matrix[0][0]);
}

void SetMat4(shader Shader, const std::string & Name, const glm::mat4 & Matrix) {
    glUniformMatrix4fv(glGetUniformLocation(Shader.ID, Name.c_str()), 1, GL_FALSE, &Matrix[0][0]);
}

void CheckShaderErrors(GLuint Shader, std::string Type) {
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