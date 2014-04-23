#ifndef FACE_HPP
#define FACE_HPP 

#include <glm/glm.hpp>
#include <stdexcept>
#include <sstream>
#include <string>

class Face {
public:
  Face(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2) 
      : v0( vertex0 ), v1(vertex1), v2(vertex2),
        normal(glm::normalize(glm::cross(vertex2 - vertex0, vertex1 - vertex0))) {
  }

  Face(const Face& other)
      : v0(other.v0), v1(other.v1), v2(other.v2), normal(other.normal) {
  };

  const glm::vec3& operator[](int index) const {
    switch (index) {
      case 0: return v0; break;
      case 1: return v1; break;
      case 2: return v2; break;
      default: throw std::out_of_range("Unvalid index of face vertex");
    }
  };

  const glm::vec3& getNormal() {
    return normal;
  };

  std::string toString() const {
    std::ostringstream string_stream;
    string_stream << "{ { " << v0.x << ", " << v0.y << ", " << v0.z << " }, { " <<
                               v1.x << ", " << v1.y << ", " << v1.z << " }, { " <<
                               v2.x << ", " << v2.y << ", " << v2.z << " } }";
    return string_stream.str();
  };

private:
  const glm::vec3 v0, v1, v2;
  const glm::vec3 normal;

};


#endif /* FACE_HPP */
