#include "RenderableObject.h"

RenderableObject::RenderableObject(Mesh *mesh, Material *material) {
  this->mesh = mesh;
  this->material = material;
}

void RenderableObject::render() {
  material->shader->use();
  material->texture->use();
  material->shader->setInt("uTexture", 0);
  mesh->draw();
}
