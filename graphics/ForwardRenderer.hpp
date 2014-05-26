#ifndef FORWARDRENDERER_HPP
#define FORWARDRENDERER_HPP 

#include <iostream>

class ForwardRenderer {
public:
  
  template<typename Renderable>
  void render(const Renderable& renderable);

};
#endif /* FORWARDRENDERER_HPP */
