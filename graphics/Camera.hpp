#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>

class Camera {

public:

  Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);

  const glm::mat4& getViewMatrix() const {
    return view_matrix;
  }


private:
  glm::vec3 pos, target, up;
  glm::mat4 view_matrix;


};

#endif
