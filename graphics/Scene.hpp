#ifndef SCENE_HPP
#define SCENE_HPP

#include "Model.hpp"
#include "Face.hpp"
#include "Camera.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <functional>

#include <assimp/scene.h>

class Scene {
public:

  typedef std::function<bool(const Model&)> Predicate;

  class MeshIterator : public std::iterator<std::input_iterator_tag, Model>{
  public:

    MeshIterator();
    MeshIterator(Predicate predicate);

    MeshIterator(std::vector<Model>::iterator iter);
    MeshIterator(const MeshIterator& other);
    ~MeshIterator();
    MeshIterator& operator=(const MeshIterator& other);

    bool operator==(const MeshIterator& other) const;
    bool operator!=(const MeshIterator& other) const;
    
    MeshIterator& operator++();

    Model& operator*() const;
    Model* operator->() const;
  private:
    const std::function<bool(const Model&)> predicate;
    std::vector<Model>::iterator iterator;
  };

  class Range {
  public:
    Range();
    Range(std::function<bool(const Model&)> predicate);
  };

  Scene();
  void addModel(Model model);

  void setCamera(Camera cam);
  Camera& getCamera();
  const Camera& getConstCamera() const;

  MeshIterator begin();
  MeshIterator end();

  std::string toString() const;

  std::vector<Model> models;
private:
  Camera camera;

};







#endif
