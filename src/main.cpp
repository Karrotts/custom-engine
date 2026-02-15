#include <iostream>

#include "core/Engine.h"
#include "core/Mesh.h"
#include "core/Texture.h"

int main() {
  Engine engine;
  Window window(1920, 1080, "Custom Engine v0.0");
  window.displayFPS(true, 20);

  if (!engine.initialize(&window)) {
    std::cout << "Failed to initialize engine!" << std::endl;
    return -1;
  }
  Shader shader = Shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Mesh mesh = Mesh({
    { glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1, 1) },
    { glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 1) },
    { glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 0) },
    { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0, 0) }
  }, {
    0, 1, 2,
    2, 3, 1
  });
  Texture texture = Texture("assets/textures/tex_DebugUVTiles.png");

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    // use shader and draw
    shader.use();
    texture.use();
    shader.setInt("uTexture", 0);
    shader.setFloat("uResolution", engine.getWindow()->getResolution());
    mesh.draw();

    engine.pollEvents();
  }

  engine.terminate();
  return 0;
}
