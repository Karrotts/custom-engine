#ifndef GAME_ENGINE_OBJLOADER_H
#define GAME_ENGINE_OBJLOADER_H
#include <fstream>
#include <sstream>
#include <string>

#include "Logger.h"
#include "../rendering/Mesh.h"

struct FaceIndexData {
  int vertex { -1 }, uv { -1 }, normal { -1 };
};

struct FaceData {
  std::vector<FaceIndexData> data;
};

struct ObjLoader {
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;
  std::vector<FaceData> faces;
  std::string name;

  ObjLoader(const char* path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line))
    {
      std::istringstream ss(line);
      std::string type;
      ss >> type;
      if (type == "o") {
        ss >> name;
      }
      if (type == "v") {
        float x, y, z;
        ss >> x >> y >> z;
        vertices.emplace_back(x, y, z);
      }
      if (type == "vn") {
        float x, y, z;
        ss >> x >> y >> z;
        normals.emplace_back(x, y, z);
      }
      if (type == "vt") {
        float u, v;
        ss >> u >> v;
        uvs.emplace_back(u, v);
      }
      if (type == "f") {
        std::string face;
        FaceData faceData;
        while (ss >> face) {
          std::istringstream ssFace(face);
          std::string token;
          std::getline(ssFace, token, '/');
          FaceIndexData faceIndexData;
          if (!token.empty()) {
            faceIndexData.vertex = std::stoi(token) - 1; // obj index starts at 1 normalize to 0 based
          }
          if (std::getline(ssFace, token, '/') && !token.empty()) {
            faceIndexData.uv = std::stoi(token) - 1;
          }
          if (std::getline(ssFace, token, '/') && !token.empty()) {
            faceIndexData.normal = std::stoi(token) - 1;
          }
          faceData.data.emplace_back(faceIndexData);
        }
        faces.emplace_back(faceData);
      }
    };
    file.close();
  }

  void toMesh() {

  }
};

#endif //GAME_ENGINE_OBJLOADER_H