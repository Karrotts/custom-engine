#include "Transform.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

Transform::Transform() {
  this->position = glm::vec3(0.0f);
  this->rotation = glm::vec4(0.0f);
  this->scale = glm::vec3(1.0f);
}

glm::mat4 Transform::getTransformationMatrix() {
  glm::mat4 transform = glm::mat4(1.0f);
  transform = glm::translate(transform, this->position);
  transform = glm::scale(transform, this->scale);
  transform = glm::rotate(transform, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  transform = glm::rotate(transform, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  transform = glm::rotate(transform, this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  return transform;
}

glm::vec3 Transform::getPosition() {
  return this->position;
}

glm::vec3 Transform::getRotation() {
  return this->rotation;
}

glm::vec3 Transform::getScale() {
  return this->scale;
}

void Transform::setPosition(glm::vec3 position) {
  this->position = position;
}

void Transform::setRotation(glm::vec3 rotation) {
  this->rotation = rotation;
}

void Transform::setScale(glm::vec3 scale) {
  this->scale = scale;
}
