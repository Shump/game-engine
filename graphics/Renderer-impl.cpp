

#include "Renderer.cpp"

#include "DeferredRenderer.hpp"
#include "ForwardRenderer.hpp"

template class Renderer<DeferredRenderer>;
template void Renderer<DeferredRenderer>::render<Scene>(const Scene& scene);

template class Renderer<ForwardRenderer>;
template void Renderer<ForwardRenderer>::render<Scene>(const Scene& scene);
