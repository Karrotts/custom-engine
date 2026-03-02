#ifndef GAME_ENGINE_EDITORCAMERA_H
#define GAME_ENGINE_EDITORCAMERA_H

#include "../core/Camera.h"

class EditorCamera : public Camera {
  public:
  float movementSpeed;
  float mouseSensitivity;
  float zoom;

  EditorCamera(Window* window, CameraMode mode = PERSPECTIVE, float near = 0.1f, float far = 100.0f, float fov = 45.0f)
    : Camera(window, mode, near, far, fov), movementSpeed(5.0f), mouseSensitivity(0.1), zoom(0) {
  }

  void processKeyboardInput(double deltaTime);
  void processMouseInput();
  void processMouseScrollInput();

  private:
  glm::vec2 lastMos;
  bool firstMouse;

};


#endif //GAME_ENGINE_EDITORCAMERA_H