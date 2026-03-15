#ifndef GAME_ENGINE_TRANSFORMCOMPONENT_H
#define GAME_ENGINE_TRANSFORMCOMPONENT_H

#include "../NodeComponent.h"
#include "../../core/math/Transform.h"


class TransformComponent : public NodeComponent {
  public:
  Transform* getTransform();
  NodeComponent* deserialize() override;
  std::string serialize() override;
  glm::mat4 getTransformMatrix();

  private:
  Transform transform;
};


#endif //GAME_ENGINE_TRANSFORMCOMPONENT_H