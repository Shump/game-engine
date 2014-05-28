#include "opengl.hpp"

#include "ShaderProgram.hpp"

#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram() : is_loaded(false) {

}

ShaderProgram::ShaderProgram(std::initializer_list<Shader> list) : shaders(list) {
  
  shader_program = glCreateProgram();

  for(Shader shader : shaders) {
    glAttachShader(shader_program, shader.shader);
  }

  // TODO: Fix proper data location binding!
  glBindFragDataLocation(shader_program, 0, "outColor");

  // TODO: Fix dynamic attribute stuff
  glBindAttribLocation(shader_program, position_index, "position"); // The index for "position" input in the vertex shader is hardcoded for position_index.

  glLinkProgram(shader_program);

  is_loaded = true;
}

GLuint ShaderProgram::getGLShaderProgram() {
  if (!is_loaded) {
    throw std::runtime_error("ShaderProgram::getGLShaderProgram: The shaderprogram has not been initialized.");
  }
  return shader_program;
}

void ShaderProgram::setUniform(const std::string& name, float value) {
  GLint location = glGetUniformLocation(shader_program, name.c_str());
  glUniform1f(location, value);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value) {
  GLint location = glGetUniformLocation(shader_program, name.c_str());
  glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& value) {
  GLint location = glGetUniformLocation(shader_program, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
  
