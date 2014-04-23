#include "GraphicsEngine.hpp"
#include "opengl.hpp"
#include <string>

void GraphicsEngine::setShaderProgram(std::shared_ptr<ShaderProgram> program) {
  GraphicsEngine::program = program;

  glUseProgram(program->shader_program);
}

void GraphicsEngine::init() {
  if(!glfwInit()) {
    //TODO: Through error exception!
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GraphicsEngine::start(unsigned int width, unsigned int height, std::string title) {
  
  if(!glfwOpenWindow(width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
    glfwTerminate();
    return;
  }

  // Set window title AFTER window is open.
  glfwSetWindowTitle(title.c_str());

  //glfwDisable(GLFW_MOUSE_CURSOR);
}

void GraphicsEngine::drawModel(const Model& model) {

  glBindVertexArray(model.getVertexArrayObject());

  glDrawArrays(GL_TRIANGLES, 0, model.getNumberVertices());

}

void GraphicsEngine::drawScene(const Scene& scene) {
  for(Model* model : scene.models) {
    drawModel(*model);
  }
}

void GraphicsEngine::render() {
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers();
}





