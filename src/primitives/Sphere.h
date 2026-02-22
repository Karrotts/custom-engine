#ifndef GAME_ENGINE_SPHERE_H
#define GAME_ENGINE_SPHERE_H
#include <cmath>
#include "../core/Mesh.h"
#include "glm/ext/scalar_constants.hpp"

Mesh createSphere(float radius, int segments = 16) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  float pi = glm::pi<float>();
  float twoPi = 2.0f * pi;

  // Generate vertices
  for (int i = 0; i <= segments; i++) {
    float stackAngle = pi / 2 - i * pi / segments; // from pi/2 to -pi/2
    float xy = radius * cos(stackAngle);
    float z = radius * sin(stackAngle);

    for (int j = 0; j <= segments; j++) {
      float sectorAngle = j * twoPi / segments; // from 0 to 2pi

      float x = xy * cos(sectorAngle);
      float y = xy * sin(sectorAngle);

      glm::vec3 position(x, y, z);
      glm::vec3 normal = glm::normalize(position);
      glm::vec2 uv(static_cast<float>(j) / segments, static_cast<float>(i) / segments);

      vertices.push_back(Vertex(position, normal, uv));
    }
  }

  // Generate indices
  for (int i = 0; i < segments; i++) {
    for (int j = 0; j < segments; j++) {
      int first = i * (segments + 1) + j;
      int second = first + segments + 1;

      indices.push_back(first);
      indices.push_back(second);
      indices.push_back(first + 1);

      indices.push_back(first + 1);
      indices.push_back(second);
      indices.push_back(second + 1);
    }
  }

  return { vertices, indices };
}


#endif //GAME_ENGINE_SPHERE_H
