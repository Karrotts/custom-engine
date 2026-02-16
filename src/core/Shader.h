#ifndef GAME_ENGINE_SHADER_H
#define GAME_ENGINE_SHADER_H

#include <string>
#include <unordered_map>

#include "glad/glad.h"

class Shader {
public:
  unsigned int ID;

  Shader(const char* vertexShader, const char* fragmentShader);
  ~Shader();

  void use();

  void setBool(const std::string& name, bool value);
  void setInt(const std::string& name, int value);
  void setFloat(const std::string& name, float value);
  void setVec2f(const std::string& name, float x, float y);
  void setVec3f(const std::string& name, float x, float y, float z);
  void setVec4f(const std::string& name, float x, float y, float z, float a);
  void setVec2i(const std::string& name, int x, int y);
  void setVec3i(const std::string& name, int x, int y, int z);
  void setVec4i(const std::string& name, int x, int y, int z, int a);
  GLint getUniformLocation(const std::string& name);

private:
  std::unordered_map<std::string, GLint> uniformCache;
  int compile(const char* shader, int shaderType);
  std::string loadFile(const char* path);
};


#endif //GAME_ENGINE_SHADER_H