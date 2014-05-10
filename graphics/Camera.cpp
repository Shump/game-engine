
#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
  Camera(glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3(0.0f, 0.0f, -1.0f),
         glm::vec3(0.0f, 1.0f, 0.0f)) {

}

Camera::Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up) {
  Camera::pos = pos;
  Camera::target = target;
  Camera::up = up;
}
