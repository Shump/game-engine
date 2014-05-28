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

  proj_matrix = glm::perspective(45.0f, float(width / height), 0.1f, 100.0f);

  glEnable(GL_DEPTH_TEST);

  texture.load("data/duck.jpg");

  Shader vertex_shader("data/shader.vert");
  Shader fragment_shader("data/shader.frag");
  
  ShaderProgram shader_program{vertex_shader, fragment_shader};

  program = shader_program;
  glUseProgram(shader_program.getGLShaderProgram());

  shader_program.setUniform("triangleColor", glm::vec3(1.0, 0.0, 0.0));
}

GraphicsEngine::~GraphicsEngine() {
  glfwTerminate();
}

void GraphicsEngine::drawModel(const glm::mat4& view_mat, const Model& model) {

    glBindVertexArray(model.getVertexArrayObject());
    glBindBuffer(GL_ARRAY_BUFFER, model.getVerticesVBO());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getTextureId());

    program.setUniform("model_mat", model.getModelMatrix());
    program.setUniform("view_mat", view_mat);
    program.setUniform("proj_mat", proj_matrix);
    program.setUniform("triangleColor", glm::vec3(0.0, 1.0, 0.0));

    program.setUniform("ambient_color", glm::vec3(7.0f, 7.0, 1.0));
    program.setUniform("ambient_intensity", 0.1f);
    program.setUniform("sun_dir", glm::vec3(1.0f, 1.0f, 1.0f));
    program.setUniform("sun_color", glm::vec3(1.0f, 1.0f, 1.0f));
    program.setUniform("sun_intensity", 1.0);
    glDrawArrays(GL_TRIANGLES, 0, model.getNumberVertices());

}

void GraphicsEngine::render(const Scene& scene) {
  glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const glm::mat4& view_mat = scene.getConstCamera().getViewMatrix();

  for(const auto& model : scene.models) {
    drawModel(view_mat, model);
  }

  Renderer<DeferredRenderer> dr((DeferredRenderer()));

  Renderer<ForwardRenderer> fr((ForwardRenderer(program)));
}

void GraphicsEngine::swapBuffers() {
  glfwSwapBuffers(window);

}





