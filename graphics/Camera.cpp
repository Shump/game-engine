
#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up) {
  view_matrix = glm::lookAt(pos, target, up);
}
