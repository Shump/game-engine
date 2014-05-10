#ifndef SCENE_HPP
#define SCENE_HPP

#include "Model.hpp"
#include "Face.hpp"
#include "Camera.hpp"

#include <memory>
#include <string>
#include <vector>

#include <assimp/scene.h>

class Scene {
public:
  Scene();
  Scene(std::vector<Model*> models);

  void addModel(Model* model);

  std::string toString() const;

  std::vector<Model*> models;

  void setCamera(Camera cam) {
    camera = cam;
  }

  Camera& getCamera() {
    return camera;
  }

  const Camera& getConstCamera() const {
    return camera;
  }

private:
  Camera camera;

};







#endif
