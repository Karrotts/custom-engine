#include "Engine.h"
#include "util/Logger.h"
#include "Window.h"
#include "glm/vec4.hpp"

// auto detect Nvidia or AMD GPU
extern "C" {
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

Engine::Engine() {
  window = nullptr;
  lastFrame = 0;
}

bool Engine::initialize(Window *window) {
  this->window = window;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  std::string openGLVersion = "OpenGL v" + std::to_string(OPENGL_MAJOR_VERSION) + "." + std::to_string(OPENGL_MINOR_VERSION);
  Logger::info("Custom Engine v0.0 - " + openGLVersion);

  glEnable(GL_DEPTH_TEST); // todo move this to camera class

  window->printDisplayInfo();
  lastFrame = glfwGetTime();

  return true;
}

double Engine::getDeltaTime() {
  return deltaTime;
}

void Engine::update() {
  this->updateDeltaTime();
  window->tick(deltaTime);
}

void Engine::terminate() {
  glfwTerminate();
}

uint32_t Engine::createShader(Shader* shader) {
  // todo: this should eventually do:
  // 1. check if the shader already exists in the cache store and return that ID instead
  shader->load();
  return shaderCache.add(shader);
}

uint32_t Engine::createTexture(Texture* texture) {
  // todo: this should eventually do:
  // 1. check if the texture already exists in the cache store and return that ID instead
  texture->load();
  return textureCache.add(texture);
}

Window * Engine::getWindow() {
  return window;
}

Engine::~Engine() {
  Logger::info("Custom Engine Closed");
}

void Engine::updateDeltaTime() {
  double currentFrame = glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
}

void Engine::render() {
  glm::vec4 clear_color = glm::vec4(0.05f, 0.05f, 0.1f, 1.00f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
}

void Engine::pollEvents() {
  glfwSwapBuffers(window->getWindow());
  glfwPollEvents();
}