#ifndef DEFERREDRENDERER_HPP
#define DEFERREDRENDERER_HPP 

#include <iostream>

class DeferredRenderer {
public:
  template<typename Renderable>
  void render(const Renderable& renderable);

};
  

#endif /* DEFERREDRENDERER_HPP */
