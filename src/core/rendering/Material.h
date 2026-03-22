#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "Color.h"
#include "Shader.h"
#include "Texture.h"

struct Material {
  Texture* albedoTexture = nullptr;
  Texture* specularTexture = nullptr;
  Shader* shader = nullptr;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;

  Material(const Material&) = delete;
  Material& operator=(const Material&) = delete;

  Material(Material&&) = default;
  Material& operator=(Material&&) = default;


  Material(Shader* shader) : shader(shader) {}

  void use() {
    shader->setVec3("material.diffuse", diffuse);
    shader->setVec3("material.specular", specular);
    shader->setVec3("material.ambient", ambient);
    shader->setFloat("material.shininess", shininess);
    shader->setBool("material.useAlbedoTexture", false);
    shader->setBool("material.useSpecularTexture", false);

    if (albedoTexture) {
      albedoTexture->textureSlot = 0;
      albedoTexture->use();
      shader->setBool("material.useAlbedoTexture", true);
      shader->setInt("material.albedoTexture", albedoTexture->textureSlot);
    }

    if (specularTexture) {
      specularTexture->textureSlot = 1;
      specularTexture->use();
      shader->setBool("material.useSpecularTexture", true);
      shader->setInt("material.specularTexture", specularTexture->textureSlot);
    }
  }
};

#endif //GAME_ENGINE_MATERIAL_H