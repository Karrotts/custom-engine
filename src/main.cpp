#include <iostream>

#include "core/Engine.h"
#include "primitives/Square.h"
#include "core/Camera.h"
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
  Mesh sphere = createSphere(0.5, 64);
  Mesh sphere2 = createSphere(0.5, 32);

  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Texture texture("assets/textures/tex_DebugUVTiles.png");

  Material mat1(&shader, &texture);
  Material mat2(&shader, &texture);

  RenderableObject renderable(&sphere, &mat1);
  renderable.transform.setPosition(glm::vec3(-1.0f, 0.0f, 0.0f));

  RenderableObject renderable2(&sphere2, &mat2);
  renderable2.transform.setPosition(glm::vec3(1.0f, 0.0f, 0.0f));

  std::vector<RenderableObject*> renderables = {&renderable, &renderable2};

  // Camera camera(&window);
  // camera.position = glm::vec3(0.0f, 0.0f, 3.0f);

  EditorCamera camera(&window);
  camera.position = glm::vec3(0.0f, 0.0f, 3.0f);


  shader.load();
  texture.load();

  shader.use();
  texture.use();

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    shader.update(&window);

    for (auto r: renderables) {
      r->render();
      shader.setMat4("uView", camera.getViewMatrix());
      shader.setMat4("uProjection", camera.getProjectionMatrix());

      glm::vec3 rotation = r->transform.getRotation();
      rotation.y += glm::radians(50.0f * engine.getDeltaTime());
      rotation.z += glm::radians(50.0f * engine.getDeltaTime());
      r->transform.setRotation(rotation);
    }

    engine.pollEvents();
    camera.processKeyboardInput(engine.getDeltaTime());
  }

  engine.terminate();
  return 0;
}
