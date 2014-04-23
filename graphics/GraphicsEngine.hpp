#ifndef GRAPHICSENGINE_HPP
#define GRAPHICSENGINE_HPP

//#define GLFW_INCLUDE_GL3
//#define GLFW_NO_GLU

#include "ShaderProgram.hpp"
#include "Scene.hpp"
#include "Model.hpp"

#include <GLFW/glfw3.h>
#include <string>
#include <memory>

class GraphicsEngine {
public:

  void setShaderProgram(std::shared_ptr<ShaderProgram> program);


  void init();
  void start(unsigned int width, unsigned int height, std::string title);
  void drawModel(const Model& model);
  void drawScene(const Scene& scene);
  void render();
  void stop();

private:

  std::shared_ptr<ShaderProgram> program;
  
};




#endif /* GRAPHICSENGINE_HPP */
