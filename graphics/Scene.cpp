
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

Scene::Scene(std::vector<Model*> new_models) {

  for(auto& model_ptr : new_models) {
    models.push_back(model_ptr);
  }

}

void Scene::addModel(Model* model) {
  model->setupGPU();
  models.push_back(model);

}

// This do not support a hierarchical scene and only one mesh!
//Scene* Scene::loadScene(const std::string& path) {
  //initLoadScene(path);
  //return result_scene;
//}

//void Scene::initLoadScene(const std::string& path) {
  //Scene::result_scene = new Scene();
  //Assimp::Importer importer;
  //Scene::ai_scene = importer.ReadFile(path, 
      //aiProcess_CalcTangentSpace       |
      //aiProcess_Triangulate            |
      //aiProcess_JoinIdenticalVertices  |
      //aiProcess_SortByPType);
  //if(!ai_scene || !ai_scene->HasMeshes()) {
    //throw std::runtime_error("Unable to load mesh!");
  //}
  //Scene::mesh = ai_scene->mMeshes[0]; // We assume there is no hiearchy in the scene
  //walkthroughScene();
//}

//void Scene::walkthroughScene() {
  //unsigned int nr_faces = mesh->mNumFaces;
  //unsigned int nr_verts = mesh->mNumVertices;

  //Model* model = new Model;
  //result_scene->models.push_back(model);
  //for(int i = 0; i < nr_faces; ++i) {
    //Face* face = buildFace(i);
    //model->addFace(face);
  //}
//}

//Face* Scene::buildFace(int faceIndex) {
      //aiFace ai_face = mesh->mFaces[faceIndex];
      //int number_of_indices = ai_face.mNumIndices;
      //glm::vec3 vertices [3];
      //for(int i = 0; i < 3; i++) {
        //int vertex_index = ai_face.mIndices[i];
        //aiVector3D vertex = mesh->mVertices[vertex_index];
        //vertices[i] = glm::vec3(vertex.x, 
                                //vertex.y, 
                                //vertex.z);
      //}
      //Face* new_face = new Face(vertices[0], vertices[1], vertices[2]);
      //return new_face;
//}

std::string Scene::toString() const {
  std::string buffer = "Scene: {\nModels: {\n";
  for(const auto model : models) {
    buffer += model->toString();
  }
  buffer += "} }";
  return buffer;
}
