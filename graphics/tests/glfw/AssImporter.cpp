
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include "AssImporter.hpp"

using namespace std;

vector<shared_ptr<Object>> AssImporter::loadObjects(const string &file) {
  auto objects = vector<shared_ptr<Object>>();

  auto obj = make_shared<Object>();

  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(file, 
                                           aiProcess_Triangulate | 
                                           aiProcess_JoinIdenticalVertices | 
                                           aiProcess_GenSmoothNormals);
  if(!scene) {
    // error 
  }

  if(!scene->HasMeshes()) {
    // error
    return objects;
  }

  objects = loadNode(scene->mRootNode, scene->mMeshes, scene->mRootNode->mTransformation);

}

vector<shared_ptr<Object>> AssImporter::loadNode(aiNode* node, aiMesh** meshes, aiMatrix4x4 par_trans) {
  vector<shared_ptr<Object>> loaded_meshes;

  aiNode** children = node->mChildren;
  int nr_children = node->mNumChildren;

  // For each child
  for_each(children, children + nr_children, [&loaded_meshes, meshes, &par_trans](aiNode* child){ 
    aiNode* child = child;
    aiMatrix4x4 trans = child->mTransformation * par_trans;
    // Load sub nodes
    auto child_objs = loadNode(child, meshes, trans);

    loaded_meshes.insert(loaded_meshes.end(), child_objs.begin(), child_objs.end());
    auto child_meshes = child->mMeshes;
    auto nr_meshes = child->mNumChildren;

    // For each child mesh
    for_each(child_meshes, child_meshes + nr_meshes, [meshes, child](unsigned int mesh_index){
      auto mesh = meshes[mesh_index];
      //auto obj = make_shared<Object>();
      //obj->vertices = new float[mesh->mNumVertices];
      //for(int i = 0; i < mesh->mNumVertices; i++) {
        
      //}
    });
  });
}


