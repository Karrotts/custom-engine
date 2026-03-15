#include "TransformComponent.h"

#include "../../core/util/Logger.h"
#include "../Node3D.h"

Transform* TransformComponent::getTransform() {
  return &transform;
}

NodeComponent* TransformComponent::deserialize() {
  Logger::error("Deserialize for TransformComponent, not implemented!");
  return this;
}

std::string TransformComponent::serialize() {
  Logger::error("Serialize for TransformComponent, not implemented!");
  return "";
}

glm::mat4 TransformComponent::getTransformMatrix() {
  Node* parent = owner;
  glm::mat4 t = getTransform()->getTransformationMatrix();
  while (parent != nullptr) {
    if (auto* n = dynamic_cast<Node3D*>(parent)) {
      t *= n->transform.getTransform()->getTransformationMatrix();
      parent = parent->getParent();
    } else {
      break;
    }
  }
  return t;
}


