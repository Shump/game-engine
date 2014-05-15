#ifndef GRAPHICSENGINE_HPP
#define GRAPHICSENGINE_HPP

#include "ShaderProgram.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "opengl.hpp"

#include <string>
#include <memory>

#include <glm/glm.hpp>

class GraphicsEngine {
public:

  ~GraphicsEngine();

  void setShaderProgram(std::shared_ptr<ShaderProgram> program);


  void init();
  void start(unsigned int width, unsigned int height, std::string title);
  void drawModel(const glm::mat4& view_mat, const Model& model);
  void drawScene(const Scene& scene);
  void render();
  void stop();
  bool shouldClose() {
    return glfwWindowShouldClose(window);
  }
  void pollEvents() {
    glfwPollEvents();
  }
  
  const glm::mat4& getProjMatrix() const {
    return proj_matrix;
  }

  GLFWwindow* window;
private:
  Texture texture;

  std::shared_ptr<ShaderProgram> program;

  glm::mat4 proj_matrix;
  
};




#endif /* GRAPHICSENGINE_HPP */
