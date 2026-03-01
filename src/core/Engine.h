#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H

#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "util/CacheStore.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

const int OPENGL_MAJOR_VERSION = 3;
const int OPENGL_MINOR_VERSION = 3;

class Engine {
public:
  Engine();
  bool initialize(Window* window);
  double getDeltaTime();
  void update();
  void render();
  void pollEvents();
  void terminate();
  uint32_t createShader(Shader* shader);
  uint32_t createTexture(Texture* texture);
  Window* getWindow();
  ~Engine();
private:
  Window *window;
  double lastFrame;
  double deltaTime;
  CacheStore<Shader*> shaderCache;
  CacheStore<Texture*> textureCache;

  void updateDeltaTime();
};


#endif //GAME_ENGINE_ENGINE_H