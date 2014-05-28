#ifndef FORWARDRENDERER_HPP
#define FORWARDRENDERER_HPP 

#include <iostream>

#include "Scene.hpp"
#include "Camera.hpp"
#include "Model.hpp"

#include "ShaderProgram.hpp"

class ForwardRenderer {
public:

  ForwardRenderer() {};
  ForwardRenderer(const ShaderProgram& program);
  ForwardRenderer(ShaderProgram&& program);

  void render(const Scene& scene);

private:
  void render(const Model& model, const Camera& camera);

  ShaderProgram program;

};
#endif /* FORWARDRENDERER_HPP */
