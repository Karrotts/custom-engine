#include "EditorCamera.h"

void EditorCamera::processKeyboardInput(double deltaTime) {
  if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    position += movementSpeed * front * (float)deltaTime;
  if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    position -= movementSpeed * front * (float)deltaTime;
  if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    position -= glm::normalize(glm::cross(front, up)) * movementSpeed* (float)deltaTime;
  if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    position += glm::normalize(glm::cross(front, up)) * movementSpeed * (float)deltaTime;
}

void EditorCamera::processMouseInput() {
  if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glm::vec2 mosPos = window->getMousePosition();
    if (firstMouse)
    {
      lastMos.x = mosPos.x;
      lastMos.y = mosPos.y;
      firstMouse = false;
    }

    float xoffset = mosPos.x - lastMos.x;
    float yoffset = lastMos.y - mosPos.y;
    lastMos.x = mosPos.x;
    lastMos.y = mosPos.y;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
      pitch = 89.0f;
    if(pitch < -89.0f)
      pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
  } else {
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstMouse = true;
  }
}
