

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

  Model* model = new Model;
  for(unsigned int i = 0; i < nr_faces; ++i) {
    Face* face = buildFace(i);
    model->addFace(face);
  }

  model->addTexture(extractTexture());

  return model;
}

Texture AssImporter::extractTexture() {
  unsigned int material_index = ai_mesh->mMaterialIndex;
  aiMaterial* ai_material = ai_scene->mMaterials[material_index];

  aiString ai_tex_path;
  const unsigned int index = 0;
  ai_material->GetTexture(aiTextureType_DIFFUSE, index, &ai_tex_path);

  std::string tex_path(ai_tex_path.C_Str());
  tex_path.insert(0, "data/");

  return Texture(tex_path);
}

Face* AssImporter::buildFace(int face_index) {
    aiFace ai_face = ai_mesh->mFaces[face_index];
    glm::vec3 positions [3];
    glm::vec3 normals [3];
    glm::vec2 uvs[3];
    for(int i = 0; i < 3; i++) {
      int vertex_index = ai_face.mIndices[i];
      aiVector3D pos = ai_mesh->mVertices[vertex_index];
      aiVector3D normal = ai_mesh->mNormals[vertex_index];
      aiVector3D uv     = ai_mesh->mTextureCoords[0][vertex_index];
      positions[i] = glm::vec3(pos.x, pos.y, pos.z);
      normals[i] = glm::vec3(normal.x, normal.y, normal.z);
      uvs[i] = glm::vec2(uv.x, uv.y);
    }
    Face* new_face = new Face(positions[0],  positions[1],  positions[2],
                              normals[0],   normals[1],   normals[2],
                              uvs[0],       uvs[1],       uvs[2]);
    return new_face;
}






