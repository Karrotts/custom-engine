#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Logger.h"
#include "Window.h"
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
    } else {
        Logger::debug("Shader Loaded: " + std::to_string(ID));
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
    GLFWwindow* window = glfwGetCurrentContext();

    // pass in time as uTime
    float time = glfwGetTime();
    glUniform1f(getUniformLocation("uTime"), time);

    // pass in resolution as uResolution
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glUniform2f(getUniformLocation("uResolution"), width, height);

    // pass in the mouse position as uMouse
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
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


Shader::~Shader() {
    Logger::debug("Unloaded Shader: " + std::to_string(ID));
    glDeleteProgram(ID);
}
