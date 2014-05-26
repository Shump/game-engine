
#include "Scene.hpp"

#include "ForwardRenderer.cpp"
#include "DeferredRenderer.cpp"

template void ForwardRenderer::render(const Scene& renderable);
template void DeferredRenderer::render(const Scene& renderable);
