

#include "Renderer.cpp"

#include "DeferredRenderer.hpp"

template class Renderer<DeferredRenderer>;
template void Renderer<DeferredRenderer>::render<Scene>(const Scene& scene);
