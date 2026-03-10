#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "Color.h"
#include "Shader.h"
#include "Texture.h"

struct Material {
  Texture* albedoTexture = nullptr;
  Color albedoColor;

  Material() : albedoColor(WHITE) {}

  void use(Shader* shader) {
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