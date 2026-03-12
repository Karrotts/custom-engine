#include <iostream>

#include "core/Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "core/util/ObjLoader.h"
#include "editor/EditorCamera.h"
#include "primitives/Primitives.h"
#include "primitives/Sphere.h"
#include "core/rendering/Material.h"
#include "core/rendering/Camera.h"
#include "core/rendering/Model.h"
#include "primitives/Primitives.h"
#include "core/util/MtlLoader.h"


int main() {
  Engine engine;
  Window window(1920, 1080, "Custom Engine v0.0");
  window.displayFPS(true, 20);

  if (!engine.initialize(&window)) {
    std::cout << "Failed to initialize engine!" << std::endl;
    return -1;
  }

  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  Texture texture("assets/textures/tex_DebugUVTiles.png");

  engine.createShader(&shader);
  engine.createTexture(&texture);

  ObjLoader cubeObj("assets/meshes/complex/dog.obj");
  std::map<std::string, std::unique_ptr<Mesh>> meshes = cubeObj.getMeshes();
  MtlLoader mtlLoader("assets/meshes/complex/dog.mtl");
  std::map<std::string, std::unique_ptr<Material>> materials = mtlLoader.getMaterials(&shader);

  Material mat1(&shader);
  mat1.albedoTexture = &texture;
  mat1.albedoColor = Color::fromRGBA(glm::vec4(255.0f, 0.0f, 0.0f, 1.0f));

  Model m(std::move(meshes), std::move(materials), &shader);

  EditorCamera camera(&window, PERSPECTIVE, 0.1, 1000);
  camera.position = glm::vec3(0.0f, 0.0f, 3.0f);

  shader.use();

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    shader.update(&window);
    m.render();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    engine.pollEvents();
    camera.process(engine.getDeltaTime());
  }

  engine.terminate();
  return 0;
}
