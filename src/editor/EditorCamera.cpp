#include "EditorCamera.h"

void EditorCamera::processKeyboardInput(double deltaTime) {
  const float cameraSpeed = 5.0f;
  if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    position += cameraSpeed * front * (float)deltaTime;
  if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    position -= cameraSpeed * front * (float)deltaTime;
  if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    position -= glm::normalize(glm::cross(front, up)) * cameraSpeed * (float)deltaTime;
  if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    position += glm::normalize(glm::cross(front, up)) * cameraSpeed * (float)deltaTime;
}
