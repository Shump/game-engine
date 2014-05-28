
#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera(const Orientation& orientation, const Lens& lens) :
    projection_matrix(glm::perspective(lens.fov, lens.ratio, lens.near_plane, lens.far_plane)) {
  Camera::pos = orientation.pos;
  Camera::dir = glm::normalize(orientation.dir);
  Camera::up = glm::normalize(orientation.up);
}

void Camera::move(const glm::vec3& move_dir) {
  pos = pos + move_dir;
}

void Camera::rotatePitch(const float angle) { // Up and down
  glm::vec3 axis = glm::cross(dir, up);
  dir = glm::rotate(dir, angle, axis);
}

void Camera::rotateYaw(const float angle) { // Left and right
  dir = glm::rotateZ(dir, -angle);
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(pos, pos + dir, up);
}

const glm::mat4& Camera::getProjectionMatrix() const {
  return projection_matrix;
}

const glm::vec3 Camera::getViewDir() const {
  return dir;
}

const glm::vec3 Camera::getLeftDir() const {
  return glm::normalize(glm::cross(up, dir));
}

const glm::vec3 Camera::getRightDir() const {
  return glm::normalize(glm::cross(dir, up));
}
