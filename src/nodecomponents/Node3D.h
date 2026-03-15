#ifndef GAME_ENGINE_NODE3D_H
#define GAME_ENGINE_NODE3D_H

#include "Node.h"
#include "components/TransformComponent.h"

class Node3D : public Node {
  public:
  Node3D();
  virtual ~Node3D() = default;
  TransformComponent transform;
};


#endif //GAME_ENGINE_NODE3D_H