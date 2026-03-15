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
#include "nodecomponents/Node3D.h"
#include "nodecomponents/components/ModelComponent.h"


int main() {

  //  ====== CREATE ENGINE ========
  Engine engine;
  if (!engine.initialize(1920, 1080, "Custom Engine v0.0")) {
    std::cout << "Failed to initialize engine!" << std::endl;
    return -1;
  }

  // ====== SET WINDOW TO DISPLAY FPS ======
  WindowManager::getInstance().getActiveWindow()->displayFPS(true, 20);

  // ====== DEFAULT SHADER ======
  Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
  engine.createShader(&shader);
  shader.use();

  // ====== TEXTURE EXAMPLE ======
  // Texture texture("assets/textures/tex_DebugUVTiles.png");
  // engine.createTexture(&texture);

  // ====== DEFAULT MATERIAL & MODEL ======
  Material defaultMat(&shader);
  Model m = Model::fromFile("assets/meshes/complex/house.obj", "assets/meshes/complex/house.mtl", &defaultMat);

  // ====== EDITOR CAMERA ======
  EditorCamera camera(PERSPECTIVE, 0.1, 1000);
  camera.position = glm::vec3(0.0f, 0.0f, 3.0f);

  // ====== NODE SETUP ========
  Node3D environment{};
  ModelComponent worldModel(&m);
  environment.addComponent(&worldModel);

  // dog
  Node3D dog{};
  Model dogModel = Model::fromFile("assets/meshes/complex/dog.obj", "assets/meshes/complex/dog.mtl", &defaultMat);
  ModelComponent dogModelComponent(&dogModel);
  dog.transform.getTransform()->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
  dog.transform.getTransform()->setRotation(glm::vec3(0.0f, 1.570796f, 0.0f));
  dog.transform.getTransform()->setPosition(glm::vec3(0.0f, 1.5f, 3.0f));
  dog.addComponent(&dogModelComponent);

  Node3D root{};
  root.addChild(&environment);
  root.addChild(&dog);


  // ====== PROCESS ===========
  while (!engine.shouldClose()) {
    engine.update();
    engine.render();

    shader.update();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    root.process(engine.getDeltaTime());

    engine.pollEvents();
    camera.process(engine.getDeltaTime());
  }

  engine.terminate();
  return 0;
}
