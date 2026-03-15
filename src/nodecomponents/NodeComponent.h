#ifndef GAME_ENGINE_NODECOMPONENT_H
#define GAME_ENGINE_NODECOMPONENT_H

#include "Node.h"
#include <string>

class Node;

class NodeComponent {
  public:
  Node* owner;
  virtual ~NodeComponent() = default;
  virtual NodeComponent* deserialize() = 0;
  virtual std::string serialize() = 0;
  virtual void process(float delta) {};
};

#endif //GAME_ENGINE_NODECOMPONENT_H