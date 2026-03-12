#ifndef GAME_ENGINE_MTLLOADER_H
#define GAME_ENGINE_MTLLOADER_H

#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

#include "glm/vec3.hpp"

struct Material;
class Shader;

struct Mtl {
  std::string materialName;
  float Ns;
  glm::vec3 Ka;
  glm::vec3 Kd;
  glm::vec3 Ks;
  glm::vec3 Ke;
  float Ni;
  float d;
  int illum;
};

struct MtlLoader {
  std::vector<Mtl> mtls;

  MtlLoader(const char* path) {
    std::ifstream file(path);
    std::string line;
    Mtl mtl;
    while (std::getline(file, line)) {
      std::istringstream ss(line);
      std::string type;
      ss >> type;
      if (type == "newmtl") {
        std::string materialName;
        ss >> materialName;
        if (!mtl.materialName.empty()) {
          mtls.push_back(mtl);
          mtl = Mtl();
        }
        mtl.materialName = materialName;
      }
      if (type == "Ns") {
        float Ns;
        ss >> Ns;
        mtl.Ns = Ns;
      }
      if (type == "Ka") {
        float x, y, z;
        ss >> x >> y >> z;
        mtl.Ka = glm::vec3(x, y, z);
      }
      if (type == "Kd") {
        float x, y, z;
        ss >> x >> y >> z;
        mtl.Kd = glm::vec3(x, y, z);
      }
      if (type == "Ks") {
        float x, y, z;
        ss >> x >> y >> z;
        mtl.Ks = glm::vec3(x, y, z);

      }
      if (type == "Ke") {
        float x, y, z;
        ss >> x >> y >> z;
        mtl.Ke = glm::vec3(x, y, z);
      }
      if (type == "Ni") {
        float Ni;
        ss >> Ni;
        mtl.Ni = Ni;
      }
      if (type == "d") {
        float d;
        ss >> d;
        mtl.d = d;
      }
      if (type == "illum") {
        int illum;
        ss >> illum;
        mtl.illum = illum;
      }
    }
    if (!mtl.materialName.empty()) {
      mtls.push_back(mtl);
    }
  }

  std::map<std::string, std::unique_ptr<Material>> getMaterials(Shader* shader) {
    std::map<std::string, std::unique_ptr<Material>> materials;
    for (auto& it : mtls) {
      Material mat(shader);
      mat.albedoColor = Color::fromLinear(glm::vec4(it.Kd.x, it.Kd.y, it.Kd.z, 1.0));
      materials.insert({it.materialName, std::make_unique<Material>(std::move(mat))});
    }
    return materials;
  }
};

#endif //GAME_ENGINE_MTLLOADER_H