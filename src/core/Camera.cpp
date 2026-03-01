#include "Camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(Window *window, CameraMode mode, float near, float far, float fov) {
  this->window = window;
  this->mode = mode;
  this->near = near;
  this->far = far;
  this->fov = fov;
  this->projection = glm::mat4(1.0f);
  updateProjectionMatrix();
  setConfigDefault();
}

void Camera::setConfigDefault(glm::vec3 position, glm::vec3 up, float yaw, float pitch, glm::vec3 front) {
  this->position = position;
  this->worldUp = up;
  this->yaw = yaw;
  this->pitch = pitch;
  this->front = front;
  updateCameraVectors();
}

glm::mat4 Camera::getProjectionMatrix() {
  return projection;
}

glm::mat4 Camera::getViewMatrix() {
  updateCameraVectors(); // maybe bad for performance to recalc these each frame
  return glm::lookAt(position, position + front, up);
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

void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  this->front = glm::normalize(front);
  right = glm::normalize(glm::cross(this->front, worldUp));
  up    = glm::normalize(glm::cross(right, this->front));
}


