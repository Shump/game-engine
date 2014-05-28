#ifndef CAMERA_HPP
#define CAMERA_HPP 

#include <glm/glm.hpp>

class Camera {

public:
  struct Orientation {
    Orientation() {};
    Orientation(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up) :
      pos(pos), dir(dir), up(up) {};
    const glm::vec3 pos, dir, up;
  };

  struct Lens {
    Lens() : fov(0.f), ratio(0.f), near_plane(0.f), far_plane(0.f) {};
    Lens(float fov, float ratio, float near_plane, float far_plane) :
      fov(fov), ratio(ratio), near_plane(near_plane), far_plane(far_plane) {};
    const float fov, ratio, near_plane, far_plane;
  };

  Camera() {};
  Camera(const Orientation& orientation, const Lens& lens);
  Camera(const Camera& camera) = default;
  Camera(Camera&& camera) = default;
  Camera& operator=(const Camera& camera) = default;
  Camera& operator=(Camera&& camera) = default;

  void move(const glm::vec3& move_dir);
  void rotatePitch(const float angle);
  void rotateYaw(const float angle);

  glm::mat4 getViewMatrix() const;
  const glm::mat4& getProjectionMatrix() const;

  const glm::vec3 getViewDir() const;
  const glm::vec3 getLeftDir() const;
  const glm::vec3 getRightDir() const;

private:
  glm::vec3 pos, dir, up;
  glm::mat4 projection_matrix;
};

#endif
