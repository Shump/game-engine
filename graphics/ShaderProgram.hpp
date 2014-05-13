#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "Shader.hpp"

#include <initializer_list>
#include <vector>

#include "opengl.hpp"
#include <glm/glm.hpp>

class ShaderProgram {
public:
  GLuint shader_program;

  GLuint position_index = 0;

  ShaderProgram(std::initializer_list<Shader> list);

  void setUniform(const std::string& name, float value);
  void setUniform(const std::string& name, const glm::vec3& value);
  void setUniform(const std::string& name, const glm::mat4& value);

private:
  std::vector<Shader> shaders;

};









#endif
