#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "Shader.hpp"

#include <initializer_list>
#include <vector>

#include "opengl.hpp"
#include <glm/glm.hpp>

class ShaderProgram {
public:

  GLuint position_index = 0;

  ShaderProgram();
  ShaderProgram(std::initializer_list<Shader> list);

  GLuint getGLShaderProgram();

  void setUniform(const std::string& name, float value);
  void setUniform(const std::string& name, const glm::vec3& value);
  void setUniform(const std::string& name, const glm::mat4& value);

private:
  bool is_loaded = false;
  std::vector<Shader> shaders;
  GLuint shader_program;
};









#endif
