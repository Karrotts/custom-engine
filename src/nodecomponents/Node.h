#ifndef GAME_ENGINE_NODE_H
#define GAME_ENGINE_NODE_H
#include <vector>
#include "NodeComponent.h"

class NodeComponent;

class Node {
  public:
  virtual ~Node() = default;
  void process(float delta);
  void addChild(Node* child);
  void removeChild(Node* child);
  std::vector<Node*> getChildren();
  Node* getParent();
  void addComponent(NodeComponent* component);

  template<typename T>
  T* getComponent();

  protected:
  Node* parent = nullptr;
  std::vector<Node*> children;
  std::vector<NodeComponent*> components;
};

#endif //GAME_ENGINE_NODE_H
