
#include "Shader.hpp"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

std::string Shader::file;

Shader::Shader(string path) {
  Shader::shader = loadShader(path);
}

GLuint Shader::loadShader(string path) {
  file = path;
  GLenum type = getShaderType();
  string source = loadSourceCode();
  return createAndCompileShader(type, source);
}

GLenum Shader::getShaderType() {
  string extension = file.substr(file.find_last_of(".") + 1);
  if(boost::algorithm::iequals(extension, "vert")) {
    return GL_VERTEX_SHADER;
  } else if(boost::algorithm::iequals(extension, "frag")) {
    return GL_FRAGMENT_SHADER;
  } else {
    return NULL; // TODO: Error handling!
  }
}

string Shader::loadSourceCode() {
  ifstream shaderFile(file);
  stringstream buffer;
  buffer << shaderFile.rdbuf();
  return buffer.str();
}

GLuint Shader::createAndCompileShader(GLenum type, string source) {
  GLuint shader_index = glCreateShader(type);

  const int NUMBER_OF_SHADER_SOURCES = 1;
  const int* SOURCE_LENGTHS = NULL; // NULL equals null-terminated strings
  const char* SOURCE = source.c_str();
  glShaderSource(shader_index, NUMBER_OF_SHADER_SOURCES, &SOURCE, SOURCE_LENGTHS);
  glCompileShader(shader_index);

  checkForError(shader_index);
}

void Shader::checkForError(GLuint shader_index) {
  GLint status = GL_TRUE;
  glGetShaderiv(shader_index, GL_COMPILE_STATUS, &status);
  if(status == GL_FALSE) {
    reportError(shader_index);
  }
}

void Shader::reportError(GLuint shader_index) {
    cout << "Compile error in file: " << file << endl;
    char log[1024];
    GLsizei length = 0;
    glGetShaderInfoLog(shader_index, 1024, &length, log);
    cout << log << endl;
}
