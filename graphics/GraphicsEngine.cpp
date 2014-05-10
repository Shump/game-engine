#include "GraphicsEngine.hpp"
#include "opengl.hpp"
#include <string>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

GraphicsEngine::~GraphicsEngine() {
  glfwTerminate();
}

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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GraphicsEngine::start(unsigned int width, unsigned int height, std::string title) {

  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if(!window) {
    glfwTerminate();
    // TODO: Throw error exception!
    return;
  }

  glfwMakeContextCurrent(window);
  //glfwDisable(GLFW_MOUSE_CURSOR);

  proj_matrix = glm::perspective(45.0f, float(width / height), 1.0f, 10.0f);
}

void GraphicsEngine::drawModel(const Model& model) {

  glBindVertexArray(model.getVertexArrayObject());
  glBindBuffer(GL_ARRAY_BUFFER, model.getVertexBufferObject());

  glDrawArrays(GL_TRIANGLES, 0, model.getNumberVertices());

}

void GraphicsEngine::drawScene(const Scene& scene) {
  for(Model* model : scene.models) {
    drawModel(*model);
  }
}

void GraphicsEngine::render() {
  glfwSwapBuffers(window);

}





