#ifndef ASSIMPORTER_HPP
#define ASSIMPORTER_HPP 

#include "Scene.hpp"
#include "Model.hpp"
#include <assimp/Importer.hpp>
#include <string>

class AssImporter {
public:
  AssImporter(const std::string& path);
  Scene* getScene();
  Model* getModel();

private:
  Assimp::Importer importer;
  const aiScene* ai_scene;
  aiMesh* ai_mesh;

  Model* buildModel();
  Face* buildFace(int face_index);

};







#endif /* ASSIMPORTER_HPP */
