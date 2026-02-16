#include <iostream>

#include "core/Engine.h"
#include "prototypes/Square.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


int main() {
  Engine engine;
  Window window(1920, 1080, "Custom Engine v0.0");
  window.displayFPS(true, 20);

  if (!engine.initialize(&window)) {
    std::cout << "Failed to initialize engine!" << std::endl;
    return -1;
  }

  Square square = Square();

  while (!window.shouldClose()) {
    engine.update();
    engine.render();

    square.renderable.render();

    engine.pollEvents();
  }

  engine.terminate();
  return 0;
}
