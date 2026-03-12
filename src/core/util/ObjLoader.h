#ifndef GAME_ENGINE_OBJLOADER_H
#define GAME_ENGINE_OBJLOADER_H

#include <fstream>
#include <memory>
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
  std::map<std::string, std::vector<FaceData>> materialFaces;

  ObjLoader(const char* path) {
    std::string materialName = "engine_default";

    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line))
    {
      std::istringstream ss(line);
      std::string type;
      ss >> type;
      if (type == "usemtl") {
        ss >> materialName;
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
        materialFaces[materialName].emplace_back(faceData);
      }
    };
    file.close();
  }

  std::map<std::string, std::unique_ptr<Mesh>> getMeshes() const {
    std::map<std::string, std::unique_ptr<Mesh>> meshes;
    for (const auto& mat : materialFaces) {
      meshes.insert({mat.first, toMesh(mat.second)});
    }
    return meshes;
  }

private:
  std::unique_ptr<Mesh> toMesh(std::vector<FaceData> faces) const {
    std::vector<Vertex> cVertices;
    std::vector<unsigned int> cIndices;

    for (const auto& face : faces) {
      if (face.data.size() > 4) {
        Logger::warn("N-Gon detected, face contains ["+ std::to_string(face.data.size()) +"] vertices. Attempting to triangulate as convex shape...");
      }

      // face is too small, skip them
      if (face.data.size() < 3) continue;

      for (int i = 0; i < face.data.size() - 2; i++) {
        unsigned int size = cVertices.size();
        cVertices.emplace_back(Vertex(
          vertices[face.data[0].vertex],
          normals[face.data[0].normal],
          uvs[face.data[0].uv]
        ));

        cVertices.emplace_back(Vertex(
          vertices[face.data[i + 1].vertex],
          normals[face.data[i + 1].normal],
          uvs[face.data[i + 1].uv]
        ));

        cVertices.emplace_back(Vertex(
          vertices[face.data[i + 2].vertex],
          normals[face.data[i + 2].normal],
          uvs[face.data[i + 2].uv]
        ));

        cIndices.emplace_back(size);
        cIndices.emplace_back(size+1);
        cIndices.emplace_back(size+2);
      }
    }
    return std::make_unique<Mesh>(cVertices, cIndices);
  }
};

#endif //GAME_ENGINE_OBJLOADER_H