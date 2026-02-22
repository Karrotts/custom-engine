#include <iostream>

#include "core/Engine.h"
#include "primitives/Square.h"

#define STB_IMAGE_IMPLEMENTATION
#include "glm/ext/scalar_constants.hpp"
#include "primitives/Primitives.h"
#include "stb/stb_image.h"


int main() {
  Engine engine;
  Window window(1920, 1080, "Custom Engine v0.0");
  window.displayFPS(true, 20);

  if (!engine.initialize(&window)) {
    std::cout << "Failed to initialize engine!" << std::endl;
    return -1;
  }

  Mesh cube = createCube();
  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Texture texture("assets/textures/tex_DebugUVTiles.png");
  Material mat(&shader, &texture);
  RenderableObject renderable(&cube, &mat);

  Transform camera = Transform();
  camera.setPosition(glm::vec3(0.0f, 0.0f, -3.0f));

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    renderable.render();
    shader.setMat4("uView", camera.getTransformationMatrix());
    renderable.transform.setRotation(glm::vec3(0.0f, glfwGetTime(), glfwGetTime()));

    engine.pollEvents();
  }

  engine.terminate();
  return 0;
}
