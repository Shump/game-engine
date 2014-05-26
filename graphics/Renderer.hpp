#ifndef RENDERER_HPP
#define RENDERER_HPP 

#include "Scene.hpp"

template<typename RenderMethod>
class Renderer {
public:
  Renderer(RenderMethod rm) : rm(std::move(rm)) {};

  template<typename Renderable>
  void render(const Renderable& scene);

private:
  RenderMethod rm;
};

#endif /* RENDERER_HPP */
