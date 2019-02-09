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
    int Success;
    char InfoLog[512];

    glShaderSource(Vertex, 1, &VertexStr, NULL);
    glCompileShader(Vertex);

    // Check compile errors
    glGetShaderiv(Vertex, GL_COMPILE_STATUS, &Success);
    if (!Success) {
        glGetShaderInfoLog(Vertex, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::VERTEX_COMPILATION_FAILED\n" << InfoLog << std::endl;
    }

    // Compile Fragment Shader
    unsigned int Fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(Fragment, 1, &FragmentStr, NULL);
    glCompileShader(Fragment);

    // Check compile errors
    glGetShaderiv(Fragment, GL_COMPILE_STATUS, &Success);
    if (!Success) {
        glGetShaderInfoLog(Fragment, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::FRAGMENT_COMPILATION_FAILED\n" << InfoLog << std::endl;
    }

    // Link into shader program
    unsigned int ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, Vertex);
    glAttachShader(ShaderProgram, Fragment);
    glLinkProgram(ShaderProgram);

    // Check linking errors
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::SHADER_PROGRAM_LINK_FAILED\n" << InfoLog << std::endl;
    }

    glDeleteShader(Vertex);
    glDeleteShader(Fragment);

    Result.ID = ShaderProgram;

    return Result;
}

void UseShader(shader Shader) {
    glUseProgram(Shader.ID);
}