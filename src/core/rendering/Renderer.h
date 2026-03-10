#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H
#include <cstdint>

#include "Shader.h"
#include "Texture.h"
#include "../util/CacheStore.h"


class Renderer {
  public:
    uint32_t createShader(Shader* shader);
    uint32_t createTexture(Texture* texture);
  private:
    CacheStore<Shader*> shaderCache;
    CacheStore<Texture*> textureCache;
};


#endif //GAME_ENGINE_RENDERER_H