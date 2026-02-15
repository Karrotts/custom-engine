#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    std::string vertexShader = loadFile(vertexShaderPath);
    std::string fragmentShader = loadFile(fragmentShaderPath);

    int vertex = compile(vertexShader.c_str(), GL_VERTEX_SHADER);
    int fragment = compile(fragmentShader.c_str(), GL_FRAGMENT_SHADER);
    ID = glCreateProgram();

    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2f(const std::string& name, float x, float y) const {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3f(const std::string& name, float x, float y, float z) const {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec4f(const std::string& name, float x, float y, float z, float a) const {
    glUniform4f(getUniformLocation(name), x, y, z, a);
}

void Shader::setVec2i(const std::string& name, int x, int y) const {
    glUniform2i(getUniformLocation(name), x, y);
}

void Shader::setVec3i(const std::string& name, int x, int y, int z) const {
    glUniform3i(getUniformLocation(name), x, y, z);
}

void Shader::setVec4i(const std::string& name, int x, int y, int z, int a) const {
    glUniform4i(getUniformLocation(name), x, y, z, a);
}

int Shader::getUniformLocation(const std::string& name) const
{
    int location = glGetUniformLocation(ID, name.c_str());

    if (location == -1) {
        std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND: " << name.c_str() << std::endl;
    }
    return location;
}

int Shader::compile(const char* shader, int shaderType)
{
    int id;
    int success;
    char infoLog[512];
    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shader, NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return id;
}

std::string Shader::loadFile(const char* path)
{
    std::ifstream file;
    std::stringstream buffer;

    try
    {
        file.open(path);
        buffer << file.rdbuf();
        file.close();
    }
    catch (...)
    {
        std::cerr << "ERROR::SHADER::FAILED_TO_READ_FILE: "
            << path << std::endl;
    }

    return buffer.str();
}