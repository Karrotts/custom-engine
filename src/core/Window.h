#ifndef GAME_ENGINE_WINDOW_H
#define GAME_ENGINE_WINDOW_H

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window {
public:
  Window(int width, int height, std::string title, bool fullscreen = false);
  void setTitle(const std::string &title, bool overrideBaseTitle = true);
  void setSize(int width, int height);
  void getSize(int& width, int& height);
  void setPosition(int x, int y);
  void setFullscreen(bool fullscreen);
  void setMonitor();
  int getMonitors();
  int getMonitor();
  void displayFPS(bool display, int updateFrame = 5);
  void tick(double deltaTime);
  bool shouldClose();
  GLFWwindow* getWindow();
  void printDisplayInfo() const;
  float getResolution();
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
};


#endif //GAME_ENGINE_WINDOW_H