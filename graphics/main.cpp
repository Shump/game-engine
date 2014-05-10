
#include "GraphicsEngine.hpp"
#include "Scene.hpp"
#include "Importer.hpp"
#include "AssImporter.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Model.hpp"
#include "Face.hpp"
#include "Camera.hpp"

#include <memory>

#include <iostream>

int main() {

  GraphicsEngine ge;
  ge.init();
  ge.start(800, 600, "test");

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  
  Shader vertex_shader("data/shader.vert");
  Shader fragment_shader("data/shader.frag");
  
  std::shared_ptr<ShaderProgram> shader_program(new ShaderProgram{vertex_shader, fragment_shader});
  //ge.setShaderProgram(shader_program);
  glUseProgram(shader_program->shader_program);
  shader_program->setUniform("triangleColor", glm::vec3(1.0, 0.0, 0.0));

  //Dark::Importer importer;  
  Face* face = new Face(glm::vec3(0.0, 0.5, 0.0),
                        glm::vec3(0.5, -0.5, 0.0),
                        glm::vec3(-0.5, -0.5, 0.0));
  Model* model = new Model();
  model->addFace(face);
  model->rotate(180.0f, glm::vec3(0.0, 0.0, 1.0));
  model->setupGPU();
  //Scene* scene = importer.loadScene<AssImporter>("data/cube.dae");
  Scene* scene = new Scene();
  scene->addModel(model);

  Camera cam(glm::vec3(0.0f, 0.0f, -5.0f),
             glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec3(0.0f, 1.0f, 0.0f));

  while(!ge.shouldClose()) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(model->getVertexArrayObject());
    glBindBuffer(GL_ARRAY_BUFFER, model->getVertexBufferObject());

    shader_program->setUniform("model_mat", model->getModelMatrix());
    shader_program->setUniform("view_mat", cam.getViewMatrix());
    shader_program->setUniform("proj_mat", ge.getProjMatrix());
    shader_program->setUniform("triangleColor", glm::vec3(0.0, 1.0, 0.0));
    glDrawArrays(GL_TRIANGLES, 0, model->getNumberVertices());

    //ge.drawScene(*scene);
    ge.render();

    ge.pollEvents();
  }
}
