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
  Shader shader("assets/shaders/gouraud.vert", "assets/shaders/gouraud.frag");
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
  camera.position = glm::vec3(0.0f, 2.5f, 20.0f);

  // ====== NODE SETUP ========
  Node3D environment{};
  ModelComponent worldModel(&m);
  environment.addComponent(&worldModel);

  // dog
  Node3D dog{};
  Model dogModel = Model::fromFile("assets/meshes/complex/dog.obj", "assets/meshes/complex/dog.mtl", &defaultMat);
  ModelComponent dogModelComponent(&dogModel);
  dog.transform.setScale(glm::vec3(0.25f, 0.25f, 0.25f));
  dog.transform.setRotation(glm::vec3(0.0f, 3.141593f, 0.0f));
  dog.transform.setPosition(glm::vec3(0.0f, 2.0f, 1.5f));
  dog.addComponent(&dogModelComponent);

  Node3D root{};
  root.addChild(&environment);
  root.addChild(&dog);

  root.transform.setPosition(glm::vec3(0.0f, -3.0f, 0.0f));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glFrontFace(GL_CW);

  // ====== PROCESS ===========
  while (!engine.shouldClose()) {
    engine.update();
    engine.render();

    shader.update();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());

    shader.setVec3("viewPos", camera.getPosition());
    shader.setVec3("lightPos", glm::vec3(0.0f, 10.0f, 8.0f));
    shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    root.process(engine.getDeltaTime());
    camera.process(engine.getDeltaTime());

    engine.pollEvents();
  }

  engine.terminate();
  return 0;
}
