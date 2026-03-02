#ifndef GAME_ENGINE_VERTEX_H
#define GAME_ENGINE_VERTEX_H

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texCoord;
};

#endif //GAME_ENGINE_VERTEX_H