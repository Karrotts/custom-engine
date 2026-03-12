#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "Color.h"
#include "Shader.h"
#include "Texture.h"

struct Material {
  Texture* albedoTexture = nullptr;
  Shader* shader = nullptr;
  Color albedoColor;

  Material(const Material&) = delete;
  Material& operator=(const Material&) = delete;

  Material(Material&&) = default;
  Material& operator=(Material&&) = default;


  Material(Shader* shader) : albedoColor(WHITE), shader(shader) {}

  void use() {
    shader->setVec4("uAlbedoColor", albedoColor.linear);
    if (albedoTexture) {
      albedoTexture->textureSlot = 0;
      albedoTexture->use(); // TODO: move to cache
      shader->setBool("uUseAlbedoTexture", true);
      shader->setInt("uAlbedoTexture", albedoTexture->textureSlot);
    }
  }
};

#endif //GAME_ENGINE_MATERIAL_H