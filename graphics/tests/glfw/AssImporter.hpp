#ifndef ASSIMPORTER_HPP
#define ASSIMPORTER_HPP

#include <memory>
#include <string>
#include <vector>
#include "Object.hpp"

using namespace std;

class AssImporter {

public:
  static vector<shared_ptr<Object>> loadObjects(const string &file);

private:
  static vector<shared_ptr<Object>> loadNode(aiNode* node, aiMesh** meshes, aiMatrix4x4 trans);
  

};

#endif
