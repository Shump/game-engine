

#include "AssImporter.hpp"
#include "Scene.hpp"
#include "Face.hpp"
#include "Camera.hpp"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <exception>


using namespace Assimp;

AssImporter::AssImporter(const std::string& path) : importer() {
  ai_scene = importer.ReadFile(path, 
      aiProcess_GenSmoothNormals       |
      aiProcess_CalcTangentSpace       |
      aiProcess_Triangulate            |
      aiProcess_JoinIdenticalVertices  |
      aiProcess_PreTransformVertices   |
      aiProcess_SortByPType);
  if(!ai_scene || !ai_scene->HasMeshes()) {
    throw std::runtime_error("Unable to load mesh!");
  }
  ai_mesh = ai_scene->mMeshes[0]; // We assume there is no hiearchy in the scene
}

// This do not support a hierarchical scene and only one mesh!
Scene* AssImporter::getScene() {
  Scene* result_scene = new Scene();

  Camera cam = buildCamera();
  result_scene->setCamera(cam);
  Model* model = buildModel();
  result_scene->addModel(model);
  return result_scene;
}

Camera AssImporter::buildCamera() {
  if(ai_scene->HasCameras()) {
  aiCamera* ai_cam = ai_scene->mCameras[0];
  aiVector3D pos = ai_cam->mPosition;
  aiVector3D dir = ai_cam->mLookAt;
  aiVector3D up = ai_cam->mUp;

  return Camera(glm::vec3(pos.x, pos.y, pos.z),
                glm::vec3(dir.x, dir.y, dir.z),
                glm::vec3(0.0f, 1.0f,0.0f));
  } else {
    std::string file = __FILE__;
    std::string func = __func__;
    std::string line = std::to_string(__LINE__ + 1);
    throw std::runtime_error("In " + file + ":\n\t" + func + ":" + line + ":" +
        "No existing camera!");
  }
}

Model* AssImporter::getModel() {
  return buildModel();
}

Model* AssImporter::buildModel() {
  unsigned int nr_faces = ai_mesh->mNumFaces;
  //unsigned int nr_verts = ai_mesh->mNumVertices;

  Model* model = new Model;
  for(unsigned int i = 0; i < nr_faces; ++i) {
    Face* face = buildFace(i);
    model->addFace(face);
  }
  return model;
}

Face* AssImporter::buildFace(int face_index) {
    aiFace ai_face = ai_mesh->mFaces[face_index];
    //int number_of_indices = ai_face.mNumIndices;
    glm::vec3 vertices [3];
    glm::vec3 normals [3];
    for(int i = 0; i < 3; i++) {
      int vertex_index = ai_face.mIndices[i];
      aiVector3D vertex = ai_mesh->mVertices[vertex_index];
      aiVector3D normal = ai_mesh->mNormals[vertex_index];
      vertices[i] = glm::vec3(vertex.x, vertex.y, vertex.z);
      normals[i] = glm::vec3(normal.x, normal.y, normal.z);
    }
    Face* new_face = new Face(vertices[0], vertices[1], vertices[2],
                              normals[0], normals[1], normals[2]);
    return new_face;
}






