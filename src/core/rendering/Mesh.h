#ifndef GAME_ENGINE_MESH_H
#define GAME_ENGINE_MESH_H

#include <vector>
#include "Vertex.h"
#include "glad/glad.h"

enum MeshDrawMode {
  ELEMENT,
  TRIANGLE
};

struct Mesh {
  unsigned int VBO = 0, VAO = 0, EBO = 0;
  int materialIndex = 0;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  MeshDrawMode mode;

  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;

  Mesh(Mesh&&) = default;
  Mesh& operator=(Mesh&&) = default;

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    : vertices(std::move(vertices)), indices(std::move(indices))
  {
    create();
  }

  Mesh(std::vector<Vertex> vertices)
    : vertices(std::move(vertices))
  {
    create();
  }

  void create() {
    mode = TRIANGLE;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    if (!indices.empty()) {
      glGenBuffers(1, &EBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

      glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int) * indices.size(),
        indices.data(),
        GL_STATIC_DRAW
      );
      mode = ELEMENT;
    }

    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(Vertex) * vertices.size(),
      vertices.data(),
      GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void draw() {
    glBindVertexArray(VAO);
    if (mode == ELEMENT) {
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    } else {
      glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    glBindVertexArray(0);
  }

  void clean() {
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);

    VAO = 0;
    VBO = 0;
    EBO = 0;
  }

  ~Mesh() {
    Logger::warn("Mesh instance has been removed...");
    clean();
  }
};

#endif // GAME_ENGINE_MESH_H