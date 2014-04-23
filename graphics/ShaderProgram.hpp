#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "Shader.hpp"

#include <initializer_list>
#include <vector>

#include <GLFW/glfw3.h>


class ShaderProgram {
public:
  GLuint shader_program;

  GLuint position_index = 0;

  ShaderProgram(std::initializer_list<Shader> list);

private:
  std::vector<Shader> shaders;

};









#endif SHADERPROGRAM_HPP
