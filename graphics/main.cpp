
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
  ge.setShaderProgram(shader_program);
  glUseProgram(shader_program->shader_program);
  shader_program->setUniform("triangleColor", glm::vec3(1.0, 0.0, 0.0));

  Dark::Importer importer;  
  Scene* scene = importer.loadScene<AssImporter>("data/cube.dae");

  Camera cam(glm::vec3(0.0f, 0.0f, -5.0f),
             glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec3(0.0f, 1.0f, 0.0f));
  scene->setCamera(cam);

  double time = glfwGetTime();

  while(!ge.shouldClose()) {

    double new_time = glfwGetTime();
    float delta_time = new_time - time;
    float MOVE_SPEED = 2.0f;

    Camera& camref = scene->getCamera();
    if (glfwGetKey(ge.window, GLFW_KEY_W) == GLFW_PRESS){
      camref.move(camref.getViewDir() * MOVE_SPEED * delta_time);
    }
    if (glfwGetKey(ge.window, GLFW_KEY_S) == GLFW_PRESS){
      camref.move(camref.getViewDir() * -MOVE_SPEED * delta_time);
    }
    if (glfwGetKey(ge.window, GLFW_KEY_A) == GLFW_PRESS){
      camref.move(camref.getLeftDir() * MOVE_SPEED * delta_time);
    }
    if (glfwGetKey(ge.window, GLFW_KEY_D) == GLFW_PRESS){
      camref.move(camref.getRightDir() * MOVE_SPEED * delta_time);
    }




    ge.drawScene(*scene);
    ge.render();

    ge.pollEvents();

    time = new_time;
  }
}
