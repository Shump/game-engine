#ifndef IMPORTER_HPP
#define IMPORTER_HPP 

#include "Scene.hpp"
#include "Model.hpp"

#include <string>

namespace Dark {


class Importer {
public:

  template<typename ImportMethod>
  Scene loadScene(const std::string& path) {
    ImportMethod import_method(path);
    return import_method.getScene();
  };

  template<typename ImportMethod>
  Model loadModel(const std::string& path) {
    ImportMethod import_method;
    return import_method.loadModel(path);
  };

};

}






#endif /* IMPORTER_HPP */
