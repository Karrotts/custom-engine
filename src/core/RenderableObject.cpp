#include "RenderableObject.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

RenderableObject::RenderableObject(Mesh *mesh, Material *material) {
  this->mesh = mesh;
  this->material = material;
  this->transform = Transform();
}

void RenderableObject::render() {
  material->use();
  material->shader->setMat4("uModel", transform.getTransformationMatrix());

  mesh->draw();
}
