#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:

  Camera();
  Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);

  void move(const glm::vec3& dir) {
    pos = pos + dir;
  }

  const glm::mat4 getViewMatrix() const {
    return glm::lookAt(pos, target, up);
  }

  const glm::vec3 getViewDir() const {
    return glm::normalize(target - pos);
  }

  const glm::vec3 getLeftDir() const {
    return glm::normalize(glm::cross(target - pos, up));
  }

  const glm::vec3 getRightDir() const {
    return glm::normalize(glm::cross(up, target - pos));
  }

private:
  glm::vec3 pos, target, up;
};

#endif
