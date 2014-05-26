
#include "Renderer.hpp"

template<typename RenderMethod>
template<typename Renderable>
void Renderer<RenderMethod>::render(const Renderable& renderable) {
  rm.render(renderable);
}
