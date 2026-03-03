#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "Shader.h"
#include "Texture.h"

struct Material {
  std::uint32_t shaderId;
  std::uint32_t albedoTextureId;

  Shader* shader;
  Texture* texture;

  Material(Shader* shader, Texture* texture) {
    this->shader = shader;
    this->texture = texture;
  }

  Material(std::uint32_t shaderId, std::uint32_t albedoTextureId) {
    this->shaderId = shaderId;
    this->albedoTextureId = albedoTextureId;
  }

  void use() {
    this->shader->setInt("uAlbedoTexture", 0);
  }
};

#endif //GAME_ENGINE_MATERIAL_H