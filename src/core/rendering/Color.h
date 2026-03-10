#ifndef GAME_ENGINE_COLOR_H
#define GAME_ENGINE_COLOR_H

#include "glm/vec4.hpp"

struct Color {
  glm::vec4 rgba;
  glm::vec4 linear;

  static Color fromRGBA(glm::vec4 rgba) {
    const Color c{rgba, rgbaToLinear(rgba)};
    return c;
  }

  static Color fromLinear(glm::vec4 linear) {
    const Color c{linearToRGBA(linear), linear};
    return c;
  }

  static glm::vec4 linearToRGBA(glm::vec4 linear) {
    return linear * 255.0f;
  }

  static glm::vec4 rgbaToLinear(glm::vec4 rgba) {
    return rgba / 255.0f;
  }
};

inline Color WHITE = Color::fromLinear(glm::vec4(1,1,1,1));

#endif //GAME_ENGINE_COLOR_H