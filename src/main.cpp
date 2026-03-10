#include <iostream>

#include "core/Engine.h"
#include "primitives/Square.h"
#include "core/rendering/Camera.h"
#include "primitives/Primitives.h"

#define STB_IMAGE_IMPLEMENTATION
#include "core/util/ObjLoader.h"
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

  Mesh sphere = createSphere(0.5, 16);
  Mesh sphere2 = createSphere(0.5, 32);

  ObjLoader cubeObj("assets/meshes/cube.obj");
  Mesh cube = cubeObj.toMesh();

  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Texture texture("assets/textures/tex_DebugUVTiles.png");

  engine.createShader(&shader);
  engine.createTexture(&texture);

  Material mat1;
  mat1.albedoTexture = &texture;
  mat1.albedoColor = Color::fromRGBA(glm::vec4(255.0f, 0.0f, 0.0f, 1.0f));

  RenderableObject object(&cube, &mat1);

  EditorCamera camera(&window, PERSPECTIVE, 0.1, 1000);
  camera.position = glm::vec3(0.0f, 0.0f, 3.0f);

  shader.use();

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    shader.update(&window);
    object.render(&shader);
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    engine.pollEvents();
    camera.process(engine.getDeltaTime());
  }

  engine.terminate();
  return 0;
}
