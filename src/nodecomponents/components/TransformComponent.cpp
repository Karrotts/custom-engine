#include "TransformComponent.h"

#include "../../core/util/Logger.h"
#include "../Node3D.h"

NodeComponent* TransformComponent::deserialize() {
  Logger::error("Deserialize for TransformComponent, not implemented!");
  return this;
}

std::string TransformComponent::serialize() {
  Logger::error("Serialize for TransformComponent, not implemented!");
  return "";
}

glm::mat4 TransformComponent::getLocalMatrix() {
  if (isLocalDirty) {
    local = transform.getTransformationMatrix();
    isLocalDirty = false;
  }
  return local;
}

glm::mat4 TransformComponent::getWorldMatrix() {
  if (isWorldDirty) {
    glm::mat4 localMat = getLocalMatrix();

    Node* parent = owner->getParent();

    if (auto* p = dynamic_cast<Node3D*>(parent)) {
      world =  p->transform.getWorldMatrix() * localMat;
    } else {
      world = localMat;
    }
    isWorldDirty = false;
  }

  return world;
}

glm::vec3 TransformComponent::getScale() {
  return this->transform.getScale();
}

void TransformComponent::setScale(glm::vec3 scale) {
  this->transform.setScale(scale);
  markWorldDirty();
  isLocalDirty = true;
}

glm::vec3 TransformComponent::getRotation() {
  return this->transform.getRotation();
}

void TransformComponent::setRotation(glm::vec3 rotation) {
  this->transform.setRotation(rotation);
  markWorldDirty();
  isLocalDirty = true;
}

glm::vec3 TransformComponent::getPosition() {
  return this->transform.getPosition();
}

void TransformComponent::setPosition(glm::vec3 position) {
  this->transform.setPosition(position);
  markWorldDirty();
  isLocalDirty = true;
}

void TransformComponent::markWorldDirty() {
  if (isWorldDirty) {
    return;
  }

  isWorldDirty = true;

  for (Node* child : owner->getChildren()) {
    if (auto* c = dynamic_cast<Node3D*>(child)) {
      c->transform.markWorldDirty();
    }
  }
}


