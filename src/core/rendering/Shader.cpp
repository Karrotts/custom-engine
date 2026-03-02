#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "../util/Logger.h"
#include "../Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    this->vertexPath = vertexShaderPath;
    this->fragmentPath = fragmentShaderPath;
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::load() {
    std::string vertexShader = loadFile(vertexPath);
    std::string fragmentShader = loadFile(fragmentPath);

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
        Logger::error("SHADER::FAILED_TO_LINK_PROGRAM: " + std::string(infoLog));
    } else {
        Logger::debug("Shader Loaded: " + std::to_string(ID));
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::update(Window* window) {
    // pass in time as uTime
    float time = glfwGetTime();
    glUniform1f(getUniformLocation("uTime"), time);

    // pass in resolution as uResolution
    int width, height;
    window->getSize(width, height);
    glUniform2f(getUniformLocation("uResolution"), width, height);

    // pass in the mouse position as uMouse
    double mouseX, mouseY;
    glfwGetCursorPos(window->getWindow(), &mouseX, &mouseY);
    mouseY = height - mouseY;
    float normX = static_cast<float>(mouseX) / static_cast<float>(width);
    float normY = static_cast<float>(mouseY) / static_cast<float>(height);
    glUniform2f(getUniformLocation("uMouse"), normX, normY);
}

void Shader::setBool(const std::string& name, bool value) {
    glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2f(const std::string& name, float x, float y) {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3f(const std::string& name, float x, float y, float z) {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec4f(const std::string& name, float x, float y, float z, float a) {
    glUniform4f(getUniformLocation(name), x, y, z, a);
}

void Shader::setVec2i(const std::string& name, int x, int y) {
    glUniform2i(getUniformLocation(name), x, y);
}

void Shader::setVec3i(const std::string& name, int x, int y, int z) {
    glUniform3i(getUniformLocation(name), x, y, z);
}

void Shader::setVec4i(const std::string& name, int x, int y, int z, int a) {
    glUniform4i(getUniformLocation(name), x, y, z, a);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

GLint Shader::getUniformLocation(const std::string& name) {
    if (uniformCache.find(name) != uniformCache.end())
        return uniformCache[name];

    GLint location = glGetUniformLocation(ID, name.c_str());
    uniformCache[name] = location;
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
        Logger::error("SHADER::FAILED_TO_COMPILE_SHADER: " + std::string(shader));
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
        Logger::error("SHADER::FAILED_TO_READ_FILE: " + std::string(path));
    }

    return buffer.str();
}

Shader::~Shader() {
    Logger::debug("Unloaded Shader: " + std::to_string(ID));
    glDeleteProgram(ID);
}
