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

  // garbage, replace with an actual render you loser!
  void render();
};


#endif //GAME_ENGINE_RENDERABLEOBJECT_H