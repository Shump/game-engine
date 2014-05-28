
#include "GraphicsEngine.hpp"
#include "Scene.hpp"
#include "Importer.hpp"
#include "AssImporter.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Model.hpp"
#include "Face.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

#include <memory>

#include <iostream>

int main() {

  GraphicsEngine ge(800, 600, "test");

  Dark::Importer importer;  
  Scene scene = importer.loadScene<AssImporter>("data/main.dae");

  Camera cam(glm::vec3(0.0f, -5.0f, 0.0f),
             glm::vec3(0.0f, 1.0f, 0.0f),
             glm::vec3(0.0f, 0.0f, 1.0f));

  double time = glfwGetTime();

  double old_mouse_x, old_mouse_y;
  glfwGetCursorPos(ge.window, &old_mouse_x, &old_mouse_y);

  while(!ge.shouldClose()) {

    float TURBO = 1.0f;
    if (glfwGetKey(ge.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
      TURBO = 5.0f;
    }

    double new_time = glfwGetTime();
    float delta_time = new_time - time;
    const float MOVE_SPEED = 2.5f * TURBO;

    Camera& camref = scene.getCamera();
    glm::vec3 move_dir(0.0f, 0.0f, 0.0f);
    bool moved = false;
    if (glfwGetKey(ge.window, GLFW_KEY_W) == GLFW_PRESS){
      moved = true;
      move_dir += (camref.getViewDir());
    } else if (glfwGetKey(ge.window, GLFW_KEY_S) == GLFW_PRESS){
      moved = true;
      move_dir += (-camref.getViewDir());
    }
    if (glfwGetKey(ge.window, GLFW_KEY_A) == GLFW_PRESS){
      moved = true;
      move_dir += (camref.getLeftDir());
    } else if (glfwGetKey(ge.window, GLFW_KEY_D) == GLFW_PRESS){
      moved = true;
      move_dir += (camref.getRightDir());
    }
    if (glfwGetKey(ge.window, GLFW_KEY_SPACE) == GLFW_PRESS){
      moved = true;
      move_dir += glm::vec3(0.0f, 0.0f, 1.0f);
    } else if (glfwGetKey(ge.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
      moved = true;
      move_dir += glm::vec3(0.0f, 0.0f, -1.0f);
    }

    if (moved)
      camref.move(glm::normalize(move_dir) * MOVE_SPEED * delta_time);

    double mouse_x, mouse_y;
    glfwGetCursorPos(ge.window, &mouse_x, &mouse_y);
    double delta_x = mouse_x - old_mouse_x;
    double delta_y = mouse_y - old_mouse_y;
    float ROT_SPEED = 0.1;
    
    camref.rotatePitch(-delta_y * ROT_SPEED);
    camref.rotateYaw(delta_x * ROT_SPEED);


    ge.render(scene);
    ge.swapBuffers();

    ge.pollEvents();

    time = new_time;
    old_mouse_x = mouse_x;
    old_mouse_y = mouse_y;
  }
}
