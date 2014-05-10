#ifndef SHADER_HPP
#define SHADER_HPP

#include "opengl.hpp"
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
  GLuint shader;

  Shader(std::string path);

private:
  // TODO: Extract into own shader loader class!
  std::string file;

  GLuint loadShader(std::string path);
  GLenum getShaderType();
  std::string loadSourceCode();
  GLuint createAndCompileShader(GLenum type, std::string source);
  void checkForError(GLuint shader_index);
  void reportError(GLuint shader_index);



};






#endif
