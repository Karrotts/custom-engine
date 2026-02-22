#include <iostream>

#include "core/Engine.h"
#include "primitives/Square.h"
#include "core/Camera.h"
#include "primitives/Primitives.h"

#define STB_IMAGE_IMPLEMENTATION
#include "primitives/Primitives.h"
#include "primitives/Sphere.h"
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
  Mesh sphere = createSphere(1, 64);
  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Texture texture("assets/textures/tex_DebugUVTiles.png");
  Material mat(&shader, &texture);
  RenderableObject renderable(&sphere, &mat);

  Camera camera(&window);
  camera.transform.setPosition(glm::vec3(0.0f, 0.0f, -3.0f));

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    renderable.render();
    shader.setMat4("uView", camera.transform.getTransformationMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    glm::vec3 rotation = renderable.transform.getRotation();
    rotation.y += glm::radians(50.0f * engine.getDeltaTime());
    rotation.z += glm::radians(50.0f * engine.getDeltaTime());
    renderable.transform.setRotation(rotation);

    engine.pollEvents();
  }

  engine.terminate();
  return 0;
}
