#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GL/glfw.h>

#include "ShaderProgram.hpp"


ShaderProgram::ShaderProgram(std::initializer_list<Shader> list) : shaders(list) {
  
  shader_program = glCreateProgram();

  for(Shader shader : shaders) {
    glAttachShader(shader_program, shader.shader);
  }

  // TODO: Fix proper data location binding!
  glBindFragDataLocation(shader_program, 0, "outColor");

  // TODO: Fix dynamic attribute stuff
  glBindAttribLocation(shader_program, position_index, "position");

  glLinkProgram(shader_program);

}
