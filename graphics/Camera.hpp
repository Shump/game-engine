#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera {

public:

  Camera();
  Camera(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up);

  void move(const glm::vec3& move_dir) {
    pos = pos + move_dir;
  }

  void rotatePitch(const float angle) { // Up and down
    glm::vec3 axis = glm::cross(dir, up);
    dir = glm::rotate(dir, angle, axis);
  }

  void rotateYaw(const float angle) { // Left and right
    dir = glm::rotateZ(dir, -angle);
  }

  const glm::mat4 getViewMatrix() const {
    return glm::lookAt(pos, pos + dir, up);
  }

  const glm::vec3 getViewDir() const {
    return dir;
  }

  const glm::vec3 getLeftDir() const {
    return glm::normalize(glm::cross(up, dir));
  }

  const glm::vec3 getRightDir() const {
    return glm::normalize(glm::cross(dir, up));
  }

private:
  glm::vec3 pos, dir, up;
};

#endif
