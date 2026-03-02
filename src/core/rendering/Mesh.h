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
  unsigned int VBO, VAO, EBO;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  MeshDrawMode mode;

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;
    create();
  }

  Mesh(std::vector<Vertex> vertices) {
    this->vertices = vertices;
    create();
  }

  void create() {
    mode = TRIANGLE;
    // generate vertex arrays
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // generate element buffer object
    if (indices.size() > 0) {
      glGenBuffers(1, &EBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

      // configure EBO
      glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int) * indices.size(),
        indices.data(),
        GL_STATIC_DRAW);
      mode = ELEMENT;
    }
    // configure VBO
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(Vertex) * vertices.size(),
      vertices.data(),
      GL_STATIC_DRAW);

    glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void*)offsetof(Vertex, position)
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void*)offsetof(Vertex, color)
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
      2,
      2,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (void*)offsetof(Vertex, texCoord)
    );
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void draw() {
    glBindVertexArray(VAO);
    if (mode == ELEMENT) {
      glDrawElements(GL_TRIANGLES,
        static_cast<GLsizei>(indices.size()),
        GL_UNSIGNED_INT,
        0
      );
    } else {
      glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    glBindVertexArray(0);
  }

  void clean() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

  ~Mesh() {
    clean();
  }
};

#endif //GAME_ENGINE_MESH_H