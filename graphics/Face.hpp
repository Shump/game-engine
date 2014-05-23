#ifndef FACE_HPP
#define FACE_HPP 

#include <glm/glm.hpp>
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>

class Face {
public:
  template<typename T>
  class VertexData {
  public:
    VertexData(const T& data0, const T& data1, const T& data2) :
      data0(data0), data1(data1), data2(data2) {};

    VertexData(const VertexData& other) = default;
    VertexData(VertexData&& other) = default;

    const T& operator[](int index) const {
      switch (index) {
        case 0: return data0; break;
        case 1: return data1; break;
        case 2: return data2; break;
        default: throw std::out_of_range("Unvalid index of face vertex");
      }
    };

    std::string toString() const {
      return "{{ " +
        std::to_string(data0.x) + ", " + std::to_string(data0.y) + ", " + std::to_string(data0.z) + "},{" +
        std::to_string(data1.x) + ", " + std::to_string(data1.y) + ", " + std::to_string(data1.z) + "},{" +
        std::to_string(data2.x) + ", " + std::to_string(data2.y) + ", " + std::to_string(data2.z) + "}}";
    };

    const T data0, data1, data2;
  };

  Face(const glm::vec3& location0, const glm::vec3& location1, const glm::vec3& location2,
       const glm::vec3& normal0, const glm::vec3& normal1, const glm::vec3& normal2,
       const glm::vec2& uv0    , const glm::vec2& uv1    , const glm::vec2& uv2    ) 
      : normals(normal0, normal1, normal2),
        uvs(uv0, uv1, uv2),
        coords(location0, location1, location2) {};

  Face(const Face& other) = default;
  Face(Face&& other) = default;

  std::string toString() const {
    return coords.toString();
  };

  const VertexData<glm::vec3> normals;
  const VertexData<glm::vec2> uvs;
  const VertexData<glm::vec3> coords;
};


#endif /* FACE_HPP */
