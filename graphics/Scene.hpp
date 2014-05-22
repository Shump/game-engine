#ifndef SCENE_HPP
#define SCENE_HPP

#include "Model.hpp"
#include "Face.hpp"
#include "Camera.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iterator>

#include <assimp/scene.h>

class Scene {
public:
  class MeshIterator : public std::iterator<std::input_iterator_tag, Model*>{
  public:
    MeshIterator(std::vector<Model*>::iterator iter) {
      iterator = iter;
    }

    MeshIterator(const MeshIterator& other) {
      iterator = other.iterator;
    }

    ~MeshIterator() {}

    MeshIterator& operator=(const MeshIterator& other) {
      iterator = other.iterator;
      return *this;
    }

    bool operator==(const MeshIterator& other) const {
      return iterator == other.iterator;
    }

    bool operator!=(const MeshIterator& other) const {
      return iterator != other.iterator;
    }

    MeshIterator& operator++() {
      iterator++;
      return *this;
    }
    
    Model*& operator*() const {
      return *iterator;
    }

    Model** operator->() const {
      return &*iterator;
    }
  private:
    std::vector<Model*>::iterator iterator;
  };

  Scene();
  Scene(std::vector<Model*> models);

  void addModel(Model* model);

  std::string toString() const;

  void setCamera(Camera cam) {
    camera = cam;
  }

  Camera& getCamera() {
    return camera;
  }

  const Camera& getConstCamera() const {
    return camera;
  }

  MeshIterator begin() {
    return MeshIterator(models.begin());
  }

  MeshIterator end() {
    return MeshIterator(models.end());
  }

  std::vector<Model*> models;
private:
  Camera camera;

};







#endif
