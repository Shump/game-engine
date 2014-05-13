#ifndef FACE_HPP
#define FACE_HPP 

#include <glm/glm.hpp>
#include <stdexcept>
#include <sstream>
#include <string>

class Face {
public:
  class Normals {
  public:
    Normals(glm::vec3 n0, glm::vec3 n1, glm::vec3 n2) :
      n0(n0), n1(n1), n2(n2) {};

    const glm::vec3& operator[](int index) const {
      switch (index) {
        case 0: return n0; break;
        case 1: return n1; break;
        case 2: return n2; break;
        default: throw std::out_of_range("Unvalid index of face normal");
      }
    };

  private:
    const glm::vec3 n0, n1, n2;
  };

  Face(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2,
       glm::vec3 normal0, glm::vec3 normal1, glm::vec3 normal2) 
      : normals(normal0, normal1, normal2),
        v0(vertex0), v1(vertex1), v2(vertex2) {
        
  };

  Face(const Face& other)
      : normals(other.normals[0], other.normals[1], other.normals[2]),
        v0(other.v0), v1(other.v1), v2(other.v2) {
        
  };

  const glm::vec3& operator[](int index) const {
    switch (index) {
      case 0: return v0; break;
      case 1: return v1; break;
      case 2: return v2; break;
      default: throw std::out_of_range("Unvalid index of face vertex");
    }
  };

  std::string toString() const {
    std::ostringstream string_stream;
    string_stream << "{ { " << v0.x << ", " << v0.y << ", " << v0.z << " }, { " <<
                               v1.x << ", " << v1.y << ", " << v1.z << " }, { " <<
                               v2.x << ", " << v2.y << ", " << v2.z << " } }";
    return string_stream.str();
  };

  const Normals normals;
private:
  const glm::vec3 v0, v1, v2;

};


#endif /* FACE_HPP */
