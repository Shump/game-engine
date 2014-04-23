#ifndef SHADER_HPP
#define SHADER_HPP

#include <GLFW/glfw3.h>
#include <string>

class Shader {
public:
  GLuint shader;

  Shader(std::string path);

private:
  // TODO: Extract into own shader loader class!
  static std::string file;

  static GLuint loadShader(std::string path);
  static GLenum getShaderType();
  static std::string loadSourceCode();
  static GLuint createAndCompileShader(GLenum type, std::string source);
  static void checkForError(GLuint shader_index);
  static void reportError(GLuint shader_index);


};






#endif SHADER_HPP
