#ifndef GRAPHICSENGINE_HPP
#define GRAPHICSENGINE_HPP

#include "ShaderProgram.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "opengl.hpp"

#include "ForwardRenderer.hpp"

#include <string>
#include <memory>

#include <glm/glm.hpp>

class GraphicsEngine {
public:

  GraphicsEngine(unsigned int width, unsigned int height, std::string title);
  ~GraphicsEngine();

  void render(const Scene& scene);
  void swapBuffers();
  void stop();

  bool shouldClose() {
    return glfwWindowShouldClose(window);
  }
  void pollEvents() {
    glfwPollEvents();
  }

  std::string getGLVersion() const {
    return std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
  }

  GLFWwindow* window;
private:
  void loadForwardRenderer();

  ForwardRenderer forward_renderer;

};




#endif /* GRAPHICSENGINE_HPP */
