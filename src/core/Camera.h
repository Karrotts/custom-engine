#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H

#include "Window.h"
#include "math/Transform.h"

enum CameraMode {
  ORTHOGRAPHIC,
  PERSPECTIVE
};

class Camera {
  public:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;
  float yaw;
  float pitch;

  explicit Camera(Window* window, CameraMode mode = PERSPECTIVE, float near = 0.1f, float far = 100.0f, float fov = 45.0f);

  void setConfigDefault(
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
    float yaw = -90.0f,
    float pitch = 0.0f,
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f)
  );

  glm::mat4 getProjectionMatrix();
  glm::mat4 getViewMatrix();

  protected:
  Window* window;
  CameraMode mode;
  float near;
  float far;
  float fov;
  glm::mat4 projection;
  void updateProjectionMatrix();
  void updateCameraVectors();
};


#endif //GAME_ENGINE_CAMERA_H