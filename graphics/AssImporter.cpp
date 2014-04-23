

#include "AssImporter.hpp"
#include "Scene.hpp"
#include "Face.hpp"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <exception>


using namespace Assimp;

AssImporter::AssImporter(const std::string& path) : importer() {
  ai_scene = importer.ReadFile(path, 
      aiProcess_CalcTangentSpace       |
      aiProcess_Triangulate            |
      aiProcess_JoinIdenticalVertices  |
      aiProcess_SortByPType);
  if(!ai_scene || !ai_scene->HasMeshes()) {
    throw std::runtime_error("Unable to load mesh!");
  }
  ai_mesh = ai_scene->mMeshes[0]; // We assume there is no hiearchy in the scene
}

// This do not support a hierarchical scene and only one mesh!
Scene* AssImporter::getScene() {
  Model* model = buildModel();
  Scene* result_scene = new Scene();
  result_scene->addModel(model);
  return result_scene;
}

Model* AssImporter::getModel() {
  return buildModel();
}

Model* AssImporter::buildModel() {
  unsigned int nr_faces = ai_mesh->mNumFaces;
  unsigned int nr_verts = ai_mesh->mNumVertices;

  Model* model = new Model;
  for(int i = 0; i < nr_faces; ++i) {
    Face* face = buildFace(i);
    model->addFace(face);
  }
  return model;
}

Face* AssImporter::buildFace(int face_index) {
      aiFace ai_face = ai_mesh->mFaces[face_index];
      int number_of_indices = ai_face.mNumIndices;
      glm::vec3 vertices [3];
      for(int i = 0; i < 3; i++) {
        int vertex_index = ai_face.mIndices[i];
        aiVector3D vertex = ai_mesh->mVertices[vertex_index];
        vertices[i] = glm::vec3(vertex.x, 
                                vertex.y, 
                                vertex.z);
      }
      Face* new_face = new Face(vertices[0], vertices[1], vertices[2]);
      return new_face;
}
