#ifndef GAME_ENGINE_TEXTURE_H
#define GAME_ENGINE_TEXTURE_H

#include "glad/glad.h"
#include "Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

struct Texture {
  int width, height, nrChannels;
  unsigned int texture;
  std::string texturePath;

  Texture(std::string texturePath) {
    this->texturePath = texturePath;
    load();
  }

  void use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
  }

  void load() {
    // generate texture & bind the texture to the GL_TEXTURE_2D
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    unsigned char* image = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    GLenum format;
    if (nrChannels == 1)
      format = GL_RED;
    else if (nrChannels == 3)
      format = GL_RGB;
    else if (nrChannels == 4)
      format = GL_RGBA;
    else
      format = GL_RGB; // fallback

    if (image) {
      // create a new 2D texture image
      glTexImage2D(
        GL_TEXTURE_2D,
        0, // mipmap level
        format, //texture format
        width,
        height,
        0, // legacy always zero
        format,
        GL_UNSIGNED_BYTE,
        image
      );
      glGenerateMipmap(GL_TEXTURE_2D);
      Logger::debug("Loaded Texture/Mipmap generated: " + texturePath);
    } else {
      Logger::error("Failed to load texture: " + std::string(texturePath));
    }
    stbi_image_free(image);
  }

  ~Texture() {
    glDeleteTextures(1, &texture);
    Logger::debug("Unloaded Texture: " + texturePath);
  }
};

#endif //GAME_ENGINE_TEXTURE_H