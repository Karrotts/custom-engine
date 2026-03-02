#include "Window.h"

#include <iostream>
#include <ostream>
#include <sstream>

#include "Logger.h"

void printGraphicsCardInfo() {
  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);

  std::string info =
    std::string(reinterpret_cast<const char*>(vendor)) + " | " +
    std::string(reinterpret_cast<const char*>(renderer)) + " | " +
    std::string(reinterpret_cast<const char*>(version));

  Logger::info(info);
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void windowMousePositionCallback(GLFWwindow* window, double x, double y) {
  Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (self != nullptr) {
    self->setMousePosition(x, y);
  }
}

Window::Window(int width, int height, std::string title, bool fullscreen) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW." << std::endl;
  }
  monitor = glfwGetPrimaryMonitor();
  videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? monitor : nullptr, nullptr);
  fpsInTitle = false;
  titleBase = title;
  currentFrame = 0;
  updateFrame = 0;
  fpsSum = 0;
  mousePosition = glm::vec2(static_cast<float>(width) / 2.0f,  static_cast<float>(height) / 2.0f);

  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window, windowResizeCallback);
  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, windowMousePositionCallback);
}

void Window::setTitle(const std::string &title, bool overrideBaseTitle) {
  glfwSetWindowTitle(window, title.c_str());
  if (overrideBaseTitle) {
    titleBase = title;
  }
}

void Window::setSize(int width, int height) {
  glfwSetWindowSize(window, width, height);
}

void Window::getSize(int &width, int &height) {
  glfwGetWindowSize(window, &width, &height);
}

void Window::setPosition(int x, int y) {
  glfwSetWindowPos(window, x, y);
}

void Window::setFullscreen(bool fullscreen) {
  // todo implement full screen setting
  if (fullscreen && monitor != nullptr) {
    std::cout << "Fullscreen Not Implemented" << std::endl;
  }
}

void Window::displayFPS(bool display, int updateFrame) {
  this->fpsInTitle = display;
  this->updateFrame = updateFrame;
  this->currentFrame = 0;
}

void Window::tick(double deltaTime) {
  if (fpsInTitle) {
    fpsSum += (1 / deltaTime);
    if (++currentFrame >= updateFrame) {
      currentFrame = 0;
      updateFPS();
      fpsSum = 0;
    }
  }
}

bool Window::shouldClose() {
  return glfwWindowShouldClose(window);
}

GLFWwindow * Window::getWindow() {
  return window;
}

void Window::printDisplayInfo() const {
  printGraphicsCardInfo();

  float xscale, yscale;
  glfwGetMonitorContentScale(monitor, &xscale, &yscale);

  const GLFWvidmode *mode = glfwGetVideoMode(monitor);

  int width, height;
  glfwGetMonitorPhysicalSize(monitor, &width, &height);

  const char* name = glfwGetMonitorName(monitor);

  std::string info =
    std::string(name)+ " | Size (" +
    std::to_string(mode->width) + "," + std::to_string(mode->height) + ") | " +
    "Content Scale (" + std::to_string(xscale) + "," + std::to_string(yscale) + ")";
  Logger::info("Primary Display: " + info);
}

float Window::getResolution() {
  int width, height;
  getSize(width, height);
  return static_cast<float>(width) / static_cast<float>(height);
}

glm::vec2 Window::getMousePosition() {
  return mousePosition;
}

void Window::setMousePosition(double x, double y) {
  mousePosition = glm::vec2(x, y);
}

void Window::updateFPS() {
  std::stringstream ss;
  ss << titleBase << " - FPS:" << fpsSum / updateFrame;
  setTitle(ss.str(), false);
}
