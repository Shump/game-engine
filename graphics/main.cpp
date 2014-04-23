
#include "GraphicsEngine.hpp"
#include "Scene.hpp"
#include "Importer.hpp"
#include "AssImporter.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"

#include <memory>

#include <iostream>

int main() {



  GraphicsEngine ge;
  ge.init();
  ge.start(800, 600, "test");

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  
  Dark::Importer importer;  
  Scene* scene = importer.loadScene<AssImporter>("cube.dae");

  Shader vertex_shader("shader.vert");
  Shader fragment_shader("shader.frag");
  
  ShaderProgram shader_program{vertex_shader, fragment_shader};


  while(!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED)) {
    ge.drawScene(*scene);
    ge.render();
  }
}
