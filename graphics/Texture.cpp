
#include "Texture.hpp"

#include <iostream>

#include <string>
#include <FreeImagePlus.h>

Texture::Texture(const std::string& path) {
  load(path);
}

void Texture::load(const std::string& path) {
  if (!image.load(path.c_str())) {
    std::string file = __FILE__;
    std::string func = __func__;
    std::string line = std::to_string(__LINE__ + 1);
    throw std::runtime_error("In " + file + ":\n\t" + func + ":" + line + ":" +
        "Unable to load image: " + path);
  }

  width = image.getWidth();
  height = image.getHeight();

  bits_per_pixel = image.getBitsPerPixel();
  if (bits_per_pixel == 24)
    channels = RGB;
  else if (bits_per_pixel == 32)
    channels = RGBA;

  upload();

  is_loaded = true;
}


void Texture::upload() {
  glGenTextures(1, &texture_id);

  glBindTexture(GL_TEXTURE_2D, texture_id);

  // TODO: Fix option for repeating
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenerateMipmap(GL_TEXTURE_2D);

  GLint from_format, to_format;
  switch(channels) {
    case RGB:
      from_format = GL_RGB;
      to_format = GL_BGR;
      break;
    case RGBA:
      from_format = GL_RGBA;
      to_format = GL_BGRA;
      break;
    default:
      from_format = GL_RGB;
      to_format = GL_BGR;
      break;
  }

  const GLint mipmap_level = 0;
  const GLint border = 0;
  glTexImage2D(GL_TEXTURE_2D,
               mipmap_level,
               from_format,
               width,
               height,
               border,
               to_format,
               GL_UNSIGNED_BYTE,
               image.accessPixels());


}


