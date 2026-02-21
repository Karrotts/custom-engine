#include "RenderableObject.h"

RenderableObject::RenderableObject(Mesh *mesh, Material *material) {
  this->mesh = mesh;
  this->material = material;
  this->transform = Transform();
}

void RenderableObject::render() {
  material->use();
  material->shader->setMat4("uTransform", transform.getTransformationMatrix());
  mesh->draw();
}
