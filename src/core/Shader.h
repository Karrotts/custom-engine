#ifndef GAME_ENGINE_SHADER_H
#define GAME_ENGINE_SHADER_H

#include <string>
#include <unordered_map>

#include "Window.h"
#include "glad/glad.h"
#include "glm/fwd.hpp"

class Shader {
public:
  unsigned int ID;
  const char* vertexPath;
  const char* fragmentPath;

  Shader(const char* vertexShader, const char* fragmentShader);
  ~Shader();

  void use();
  void load();
  void update(Window* window);
  void setBool(const std::string& name, bool value);
  void setInt(const std::string& name, int value);
  void setFloat(const std::string& name, float value);
  void setVec2f(const std::string& name, float x, float y);
  void setVec3f(const std::string& name, float x, float y, float z);
  void setVec4f(const std::string& name, float x, float y, float z, float a);
  void setVec2i(const std::string& name, int x, int y);
  void setVec3i(const std::string& name, int x, int y, int z);
  void setVec4i(const std::string& name, int x, int y, int z, int a);
  void setMat2(const std::string& name, const glm::mat2& mat);
  void setMat3(const std::string& name, const glm::mat3& mat);
  void setMat4(const std::string& name, const glm::mat4& matrix);
  GLint getUniformLocation(const std::string& name);

private:
  std::unordered_map<std::string, GLint> uniformCache;
  int compile(const char* shader, int shaderType);
  std::string loadFile(const char* path);
};


#endif //GAME_ENGINE_SHADER_H