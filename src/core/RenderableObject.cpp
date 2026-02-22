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

  // todo implement projection mapping
  //glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, 0.1f, 100.0f);
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1920/(float)1080, 0.1f, 100.0f);
  material->shader->setMat4("uProjection", projection);
  mesh->draw();
}
