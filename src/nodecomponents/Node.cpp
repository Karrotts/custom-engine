#include "Node.h"

void Node::process(float delta) {
  for (auto* child : children ) child->process(delta);
  for (auto* component : components ) component->process(delta);
}

void Node::addChild(Node* child) {
  child->parent = this;
  children.push_back(child);
}

void Node::removeChild(Node *child) {
  for (auto it = children.begin(); it != children.end();) {
    if (*it == child) {
      children.erase(it);
    } else {
      ++it;
    }
  }
}

std::vector<Node *> Node::getChildren() {
  return children;
}

Node * Node::getParent() {
  return parent;
}

void Node::addComponent(NodeComponent *component) {
  component->owner = this;
  components.push_back(component);
}

template<typename T>
T* Node::getComponent() {
  for (auto* c : components) {
    if (T* t = dynamic_cast<T*>(c)) return t;
  }
  return nullptr;
}

