#ifndef GAME_ENGINE_TRANSFORM_H
#define GAME_ENGINE_TRANSFORM_H

#include "glm/glm.hpp"

class Transform {
public:
  Transform();
  glm::mat4 getTransformationMatrix();
  glm::vec3 getPosition();
  glm::vec3 getRotation();
  glm::vec3 getScale();
  void setPosition(glm::vec3 position);
  void setRotation(glm::vec3 rotation);
  void setScale(glm::vec3 scale);
private:
  glm::vec3 position;
  glm::vec3 scale;
  glm::vec3 rotation;
};

#endif //GAME_ENGINE_TRANSFORM_H