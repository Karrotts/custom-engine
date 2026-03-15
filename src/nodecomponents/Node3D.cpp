#include "Node3D.h"

Node3D::Node3D() {
  transform = TransformComponent();
  transform.owner = this;
}
