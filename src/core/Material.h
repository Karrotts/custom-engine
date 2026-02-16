#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H
#include "Shader.h"
#include "Texture.h"

struct Material {
  Shader* shader;
  Texture* texture; // todo implement multiple texture support
  Material(Shader* shader, Texture* texture) {
    this->shader = shader;
    this->texture = texture;
  }
};

#endif //GAME_ENGINE_MATERIAL_H