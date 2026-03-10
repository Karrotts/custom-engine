#include "RenderableObject.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

RenderableObject::RenderableObject(Mesh *mesh, Material *material) {
  this->mesh = mesh;
  this->material = material;
  this->transform = Transform();
}

void RenderableObject::render(Shader* shader) {
  material->use(shader);
  shader->setMat4("uModel", transform.getTransformationMatrix());
  mesh->draw();
}
