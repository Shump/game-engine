#ifndef TEXTURE_HPP
#define TEXTURE_HPP 

#include "opengl.hpp"

#include <string>
#include <FreeImagePlus.h>

#include <iostream>

class Texture {
public:
  Texture(const std::string&);

  unsigned int getWidth() {
    return width;
  }

  unsigned int getHeight() {
    return height;
  }

private:
  enum Channels { RGB, RGBA } channels;
  void upload();

  fipImage image;

  unsigned int width, height;
  unsigned int bits_per_pixel;

  GLuint texture_id;


};


#endif /* TEXTURE_HPP */
