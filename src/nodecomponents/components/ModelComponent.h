#ifndef GAME_ENGINE_MODELCOMPONENT_H
#define GAME_ENGINE_MODELCOMPONENT_H

#include "TransformComponent.h"
#include "../../core/rendering/Model.h"

class ModelComponent : public NodeComponent {
  public:
  NodeComponent* deserialize() override;
  std::string serialize() override;
  void process(float delta) override;
  ModelComponent(Model* model);

  private:
  Model* model;
};


#endif //GAME_ENGINE_MODELCOMPONENT_H