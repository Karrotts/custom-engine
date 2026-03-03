#include <iostream>

#include "core/Engine.h"
#include "primitives/Square.h"
#include "core/rendering/Camera.h"
#include "primitives/Primitives.h"

#define STB_IMAGE_IMPLEMENTATION
#include "editor/EditorCamera.h"
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
  Mesh sphere = createSphere(0.5, 16);
  Mesh sphere2 = createSphere(0.5, 32);

  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Texture texture("assets/textures/tex_DebugUVTiles.png");

  engine.createShader(&shader);
  engine.createTexture(&texture);

  Material mat1(&shader, &texture);
  std::vector<RenderableObject> renderables = {};

  for (int i = 0; i < 4000; i++) {
    RenderableObject renderable(&sphere, &mat1);
    int offset = i / 50;
    renderable.transform.setPosition(glm::vec3(i - (offset * 50), 0.0f, offset));
    renderables.push_back(renderable);
  }

  EditorCamera camera(&window);
  camera.position = glm::vec3(0.0f, 0.0f, 3.0f);

  shader.use();

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    shader.update(&window);

    for (auto& r: renderables) {
      glm::vec3 rotation = r.transform.getRotation();
      rotation.y += glm::radians(50.0f * engine.getDeltaTime());
      rotation.z += glm::radians(50.0f * engine.getDeltaTime());
      r.transform.setRotation(rotation);

      r.material->texture->use();
      shader.setMat4("uView", camera.getViewMatrix());
      shader.setMat4("uProjection", camera.getProjectionMatrix());

      r.render();
    }

    engine.pollEvents();
    camera.process(engine.getDeltaTime());
  }

  engine.terminate();
  return 0;
}
