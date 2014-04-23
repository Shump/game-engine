
#include <iostream>

#include "../Scene.hpp"
#include "../Importer.hpp"
#include "../AssImporter.hpp"

int main() {

  //Scene* scene = Scene::loadScene("cube.dae");
  Dark::Importer importer;
  Scene* scene = importer.loadScene<AssImporter>("cube.dae");

  std::cout << scene->toString() << std::endl;



}
