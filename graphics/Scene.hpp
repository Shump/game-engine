#ifndef SCENE_HPP
#define SCENE_HPP

#include "Model.hpp"
#include "Face.hpp"

#include <memory>
#include <string>
#include <vector>

#include <assimp/scene.h>

class Scene {
public:
  std::vector<Model*> models;

  Scene();
  Scene(std::vector<Model*> models);

  void addModel(Model* model);

  std::string toString() const;

  //static Scene* loadScene(const std::string& path);


private:
  //std::unique_ptr<std::vector<float>> vertices = 
    //std::unique_ptr<std::vector<float>>(new std::vector<float>());
  //static void walkthroughScene();
  //static void initLoadScene(const std::string& path);
  //static Face* buildFace(int faceIndex);

  //static Scene* result_scene;
  //static const aiScene* ai_scene;
  //static aiMesh* mesh;

};







#endif SCENE_HPP
