#include <iostream>

#include "core/Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "core/util/ObjLoader.h"
#include "editor/EditorCamera.h"
#include "primitives/Primitives.h"
#include "core/rendering/Material.h"
#include "core/rendering/Camera.h"
#include "core/rendering/Model.h"
#include "core/util/MtlLoader.h"


int main() {
  Engine engine;

  if (!engine.initialize(1920, 1080, "Custom Engine v0.0")) {
    std::cout << "Failed to initialize engine!" << std::endl;
    return -1;
  }

  WindowManager::getInstance().getActiveWindow()->displayFPS(true, 20);

  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Texture texture("assets/textures/tex_DebugUVTiles.png");

  engine.createShader(&shader);
  engine.createTexture(&texture);

  Material mat1(&shader);
  mat1.albedoTexture = &texture;
  mat1.albedoColor = Color::fromRGBA(glm::vec4(255.0f, 0.0f, 0.0f, 1.0f));

  Model m = Model::fromFile("assets/meshes/complex/house.obj", "assets/meshes/complex/house.mtl", &mat1);

  EditorCamera camera( PERSPECTIVE, 0.1, 1000);
  camera.position = glm::vec3(0.0f, 0.0f, 3.0f);

  shader.use();

  while (!engine.shouldClose()) {
    engine.update();
    engine.render();

    shader.update();
    m.render();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    engine.pollEvents();
    camera.process(engine.getDeltaTime());
  }

  engine.terminate();
  return 0;
}
