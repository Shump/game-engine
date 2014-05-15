#ifndef TEXTURE_HPP
#define TEXTURE_HPP 

#include "opengl.hpp"

#include <string>
#include <FreeImagePlus.h>

#include <iostream>

class Texture {
public:
  Texture()  {};
  Texture(const std::string& path);

  void load(const std::string& path);

  unsigned int getWidth() const {
    return width;
  }

  unsigned int getHeight() const {
    return height;
  }

  GLuint getTextureId() const {
    if (is_loaded) {
      return texture_id;
    } else {
      throw std::runtime_error("Texture::getTextureId: An image has not been loaded into the texture!");
    }
  }

private:
  bool is_loaded = false;

  enum Channels { RGB, RGBA } channels;
  void upload();

  fipImage image;

  unsigned int width, height;
  unsigned int bits_per_pixel;

  GLuint texture_id;


};


#endif /* TEXTURE_HPP */
