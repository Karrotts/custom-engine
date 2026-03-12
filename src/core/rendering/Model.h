#ifndef GAME_ENGINE_MODEL_H
#define GAME_ENGINE_MODEL_H
#include <algorithm>
#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "../math/Transform.h"

struct Model {
  std::vector<std::unique_ptr<Mesh>> meshes;
  std::vector<std::unique_ptr<Material>> materials;
  Material defaultMaterial;
  Transform localTransform = Transform();

  Model(std::unique_ptr<Mesh> mesh, Shader* defaultShader) : defaultMaterial(defaultShader) {
    meshes.push_back(std::move(mesh));
  }

  Model(std::vector<std::unique_ptr<Mesh>> meshes, Shader* defaultShader) : defaultMaterial(defaultShader) {
    meshes.reserve(meshes.size());
    for (auto& mesh : meshes) {
      meshes.push_back(std::move(mesh));
    }
  }

  Model(std::unique_ptr<Mesh> mesh, std::unique_ptr<Material> material, Shader* defaultShader) : defaultMaterial(defaultShader) {
    meshes.push_back(std::move(mesh));
    materials.push_back(std::move(material));
  }

  Model(
    std::map<std::string, std::unique_ptr<Mesh>> meshMap,
    std::map<std::string, std::unique_ptr<Material>> materialMap,
    Shader* defaultShader) : defaultMaterial(defaultShader) {
    meshes.reserve(meshMap.size());
    materials.reserve(materialMap.size());
    for (auto& mesh : meshMap) {
      int matIndex = std::distance(materialMap.begin(),materialMap.find(mesh.first));
      mesh.second->materialIndex = matIndex;
      meshes.push_back(std::move(mesh.second));
    }
    for (auto& mats : materialMap) {
      materials.push_back(std::move(mats.second));
    }
  }

  void render() {
    for (auto& mesh : meshes) {
      if (mesh->materialIndex >= 0 && mesh->materialIndex < materials.size()) {
        materials[mesh->materialIndex]->use();
        materials[mesh->materialIndex]->shader->setMat4("uModel", localTransform.getTransformationMatrix());
      } else {
        defaultMaterial.use();
        defaultMaterial.shader->setMat4("uModel", localTransform.getTransformationMatrix());
      }
      mesh->draw();
    }
  }
};

#endif //GAME_ENGINE_MODEL_H