#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H
#include "Shader.h"
#include "Texture.h"

struct Material {
  Shader* shader;
  Texture* texture;
  Material(Shader* shader, Texture* texture) {
    this->shader = shader;
    this->texture = texture;
  }

  void use() {
    shader->use();
    texture->use();
    // todo implement multiple texture support
    this->shader->setInt("uTexture", 0);
  }
};

#endif //GAME_ENGINE_MATERIAL_H