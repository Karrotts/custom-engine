#ifndef GAME_ENGINE_TRANSFORMCOMPONENT_H
#define GAME_ENGINE_TRANSFORMCOMPONENT_H

#include "../NodeComponent.h"
#include "../../core/math/Transform.h"


class TransformComponent : public NodeComponent {
  public:
  NodeComponent* deserialize() override;
  std::string serialize() override;
  glm::mat4 getLocalMatrix();
  glm::mat4 getWorldMatrix();
  glm::vec3 getScale();
  void setScale(glm::vec3 scale);
  glm::vec3 getRotation();
  void setRotation(glm::vec3 rotation);
  glm::vec3 getPosition();
  void setPosition(glm::vec3 position);
  void markWorldDirty();

  private:
  Transform transform;
  glm::mat4 local;
  glm::mat4 world;
  bool isLocalDirty = true;
  bool isWorldDirty = true;
};


#endif //GAME_ENGINE_TRANSFORMCOMPONENT_H