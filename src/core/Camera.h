#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H

#include "Window.h"
#include "../math/Transform.h"

enum CameraMode {
  ORTHOGRAPHIC,
  PERSPECTIVE
};

class Camera {
  public:
  Transform transform;
  explicit Camera(Window* window, CameraMode mode = PERSPECTIVE, float near = 0.1f, float far = 100.0f, float fov = 45.0f);
  glm::mat4 getProjectionMatrix();

  private:
  Window* window;
  CameraMode mode;
  float near;
  float far;
  float fov;
  glm::mat4 projection;
  void updateProjectionMatrix();
};


#endif //GAME_ENGINE_CAMERA_H