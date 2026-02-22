#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"

Camera::Camera(Window *window, CameraMode mode, float near, float far, float fov) {
  this->window = window;
  this->mode = mode;
  this->near = near;
  this->far = far;
  this->fov = fov;
  this->projection = glm::mat4(1.0f);
  updateProjectionMatrix();
}

glm::mat4 Camera::getProjectionMatrix() {
  return projection;
}

void Camera::updateProjectionMatrix() {
  int width, height;
  window->getSize(width, height);
  if (mode == PERSPECTIVE) {
    this->projection = glm::perspective(glm::radians(this->fov), window->getResolution(), near, far);
  } else {
    this->projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), near, far);
  }
}


