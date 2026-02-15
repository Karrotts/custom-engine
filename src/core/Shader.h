#ifndef GAME_ENGINE_SHADER_H
#define GAME_ENGINE_SHADER_H

#include <string>

class Shader {
public:
  unsigned int ID;

  Shader(const char* vertexShader, const char* fragmentShader);

  void use();

  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
  void setVec2f(const std::string& name, float x, float y) const;
  void setVec3f(const std::string& name, float x, float y, float z) const;
  void setVec4f(const std::string& name, float x, float y, float z, float a) const;
  void setVec2i(const std::string& name, int x, int y) const;
  void setVec3i(const std::string& name, int x, int y, int z) const;
  void setVec4i(const std::string& name, int x, int y, int z, int a) const;
  int getUniformLocation(const std::string& name) const;

private:
  int compile(const char* shader, int shaderType);
  std::string loadFile(const char* path);
};


#endif //GAME_ENGINE_SHADER_H