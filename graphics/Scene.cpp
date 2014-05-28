
#include "Scene.hpp"
#include "Face.hpp"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <exception>

Scene::MeshIterator::MeshIterator() : predicate([](const Model&){ return true; }) {

}

Scene::MeshIterator::MeshIterator(Predicate predicate) : predicate(predicate) {

}

Scene::MeshIterator::MeshIterator(std::vector<Model>::iterator iter) {
  iterator = iter;
}

Scene::MeshIterator::MeshIterator(const MeshIterator& other) {
  iterator = other.iterator;
}

Scene::MeshIterator::~MeshIterator() {}

Scene::MeshIterator& Scene::MeshIterator::operator=(const MeshIterator& other) {
  iterator = other.iterator;
  return *this;
}

bool Scene::MeshIterator::operator==(const MeshIterator& other) const {
  return iterator == other.iterator;
}

bool Scene::MeshIterator::operator!=(const MeshIterator& other) const {
  return iterator != other.iterator;
}

Scene::MeshIterator& Scene::MeshIterator::operator++() {
  iterator++;
  return *this;
}

Model& Scene::MeshIterator::operator*() const {
  return *iterator;
}

Model* Scene::MeshIterator::operator->() const {
  return &*iterator;
}




Scene::Scene() {

}

void Scene::setCamera(Camera cam) {
  camera = Camera(std::move(cam));
}

Camera& Scene::getCamera() {
  return camera;
}

const Camera& Scene::getConstCamera() const {
  return camera;
}

Scene::MeshIterator Scene::begin() {
  return MeshIterator(models.begin());
}

Scene::MeshIterator Scene::end() {
  return MeshIterator(models.end());
}

void Scene::addModel(Model model) {
  model.setupGPU();
  models.push_back(std::move(model));
}

std::string Scene::toString() const {
  std::string buffer = "Scene: {\nModels: {\n";
  for(const auto& model : models) {
    buffer += model.toString();
  }
  buffer += "} }";
  return buffer;
}
