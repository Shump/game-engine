#include "GraphicsEngine.hpp"
#include "opengl.hpp"

#include <string>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.hpp"
#include "DeferredRenderer.hpp"
#include "ForwardRenderer.hpp"

GraphicsEngine::GraphicsEngine(unsigned int width, unsigned int height, std::string title) {
  if(!glfwInit()) {
    //TODO: Through error exception!
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if(!window) {
    glfwTerminate();
    // TODO: Throw error exception!
    return;
  }

  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glEnable(GL_DEPTH_TEST);

  loadForwardRenderer();
}

void GraphicsEngine::loadForwardRenderer() {
  Shader vertex_shader("data/shader.vert");
  Shader fragment_shader("data/shader.frag");
  
  ShaderProgram shader_program{vertex_shader, fragment_shader};

  forward_renderer = ForwardRenderer(shader_program);
}

GraphicsEngine::~GraphicsEngine() {
  glfwTerminate();
}

void GraphicsEngine::render(const Scene& scene) {
  glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  forward_renderer.render(scene);
}

void GraphicsEngine::swapBuffers() {
  glfwSwapBuffers(window);

}





