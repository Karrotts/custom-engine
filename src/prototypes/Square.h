#ifndef GAME_ENGINE_SQUARE_H
#define GAME_ENGINE_SQUARE_H
#include "../core/RenderableObject.h"

struct Square {
  Shader shader;
  Mesh mesh;
  Texture texture;
  Material material;
  RenderableObject renderable;

  Square() :
    shader("assets/shaders/default.vert", "assets/shaders/default.frag"),
    mesh({
      { glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1, 1) },
      { glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 1) },
      { glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 0) },
      { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0, 0) }
      },{
        0, 1, 2,
        2, 3, 1
      }
    ),
    texture("assets/textures/tex_DebugUVTiles.png"),
    material(&shader, &texture),
    renderable(&mesh, &material)
  { }
};

#endif //GAME_ENGINE_SQUARE_H