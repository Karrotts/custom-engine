#include "ModelComponent.h"
#include "../Node3D.h"

NodeComponent * ModelComponent::deserialize() {
  Logger::error("Deserialize for ModelComponent, not implemented!");
  return this;
}

std::string ModelComponent::serialize() {
  Logger::error("Serialize for ModelComponent, not implemented!");
  return "";
}

void ModelComponent::process(float delta) {
  if (Node3D* p = dynamic_cast<Node3D*>(owner)) {
    model->render(p->transform.getTransformMatrix());
  } else {
    model->render(glm::mat4(1.0));
  }
}

ModelComponent::ModelComponent(Model *model) : model(model) { }
