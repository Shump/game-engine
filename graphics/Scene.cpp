
#include "Scene.hpp"
#include "Face.hpp"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <exception>


using namespace Assimp;


Scene::Scene() {

}

Scene::Scene(std::vector<Model*> new_models) { // TODO: fix nice copying and stuff

  for(auto& model_ptr : new_models) {
    models.push_back(model_ptr);
  }

}

void Scene::addModel(Model* model) {
  model->setupGPU();
  models.push_back(model);

}

std::string Scene::toString() const {
  std::string buffer = "Scene: {\nModels: {\n";
  for(const auto model : models) {
    buffer += model->toString();
  }
  buffer += "} }";
  return buffer;
}
