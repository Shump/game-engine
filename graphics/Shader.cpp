
#include "Shader.hpp"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

Shader::Shader(std::string path) {
  shader = loadShader(path);
}

GLuint Shader::loadShader(std::string path) {
  file = path;
  GLenum type = getShaderType();
  std::string source = loadSourceCode();
  return createAndCompileShader(type, source);
}

GLenum Shader::getShaderType() {
  std::string extension = file.substr(file.find_last_of(".") + 1);
  if(boost::algorithm::iequals(extension, "vert")) {
    return GL_VERTEX_SHADER;
  } else if(boost::algorithm::iequals(extension, "frag")) {
    return GL_FRAGMENT_SHADER;
  } else {
    throw std::runtime_error("Shader::getShaderType: Invalid shader extension: " + extension);
  }
}

std::string Shader::loadSourceCode() {
  std::ifstream shaderFile(file);
  std::stringstream buffer;
  buffer << shaderFile.rdbuf();
  return buffer.str();
}

GLuint Shader::createAndCompileShader(GLenum type, std::string source) {
  GLuint shader_index = glCreateShader(type);

  const int NUMBER_OF_SHADER_SOURCES = 1;
  const int* NULL_TERMINATED = NULL; // NULL equals null-terminated strings
  const char* source_cstr = source.c_str();
  glShaderSource(shader_index, NUMBER_OF_SHADER_SOURCES, &source_cstr, NULL_TERMINATED);
  glCompileShader(shader_index);

  checkForError(shader_index);

  return shader_index;
}

void Shader::checkForError(GLuint shader_index) {
  GLint status = GL_FALSE;
  glGetShaderiv(shader_index, GL_COMPILE_STATUS, &status);
  if(status == GL_FALSE) {
    reportError(shader_index);
    throw std::runtime_error("Shader::checkForError: Failed compiling! See console for info log");
  }
}

void Shader::reportError(GLuint shader_index) {
  std::cout << "Compile error in file: " << file << std::endl;
  char log[1024];
  GLsizei length = 0;
  glGetShaderInfoLog(shader_index, 1024, &length, log);
  std::cout << log << std::endl;
}


