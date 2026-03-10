#ifndef GAME_ENGINE_RENDERABLEOBJECT_H
#define GAME_ENGINE_RENDERABLEOBJECT_H

#include "Material.h"
#include "Mesh.h"
#include "../math/Transform.h"

class RenderableObject {
public:
  Transform transform;
  Mesh* mesh = nullptr;
  Material* material = nullptr;
  RenderableObject(Mesh* mesh, Material* material);
  void render(Shader* shader);
};


#endif //GAME_ENGINE_RENDERABLEOBJECT_H