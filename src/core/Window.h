#ifndef GAME_ENGINE_WINDOW_H
#define GAME_ENGINE_WINDOW_H

#include <memory>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"

class Window {
public:
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  Window(Window&&) = default;
  Window& operator=(Window&&) = default;

  Window(int width, int height, std::string title, bool fullscreen = false);
  void setTitle(const std::string &title, bool overrideBaseTitle = true);
  void setSize(int width, int height);
  void getSize(int& width, int& height);
  void setPosition(int x, int y);
  void setFullscreen(bool fullscreen);
  void displayFPS(bool display, int updateFrame = 5);
  void tick(double deltaTime);
  bool shouldClose();
  GLFWwindow* getWindow();
  void printDisplayInfo() const;
  float getResolution();
  glm::vec2 getMousePosition();
  void setMousePosition(double x, double y);
  ~Window();
private:
  GLFWwindow* window;
  GLFWmonitor* monitor;
  const GLFWvidmode* videoMode;
  std::string titleBase;
  bool fpsInTitle;
  int fpsSum;
  int currentFrame;
  int updateFrame;
  void updateFPS();
  glm::vec2 mousePosition;
};

class WindowManager {
  public:
  static WindowManager& getInstance();
  Window* getActiveWindow();
  void setActiveWindow(std::unique_ptr<Window> window);

  ~WindowManager();

  private:
  std::unique_ptr<Window> activeWindow = nullptr;
};


#endif //GAME_ENGINE_WINDOW_H