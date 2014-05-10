#ifndef MODEL_HPP
#define MODEL_HPP

#include "opengl.hpp"
#include "ShaderProgram.hpp"
#include "Face.hpp"

#include <memory>
#include <vector>
#include <string>

#include <glm/glm.hpp>

using namespace std;

class Model {
public:

  Model() {};
  Model(vector<Face> faces, vector<float> vertices, vector<float> colors, shared_ptr<ShaderProgram> shader_program);
  ~Model();

  GLuint getVertexArrayObject() const;
  GLuint getVertexBufferObject() const;
  int getNumberVertices() const;
  
  void addFace(Face* face);
  void setupGPU();

  std::string toString() const;

  void setPosition(const glm::vec3& pos);
  void setRotation(const glm::vec3& rot);
  void setScale(const glm::vec3& scale);
  void setTransformation(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);

  void rotate(const float angle, const glm::vec3& axis);

  const glm::mat4& getModelMatrix() const;

private:
  void updateModelMatrix();

  bool buffers_generated = false;

  std::vector<Face> faces;
  std::vector<float> vertices;
  std::vector<float> colors;
  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
  std::shared_ptr<ShaderProgram> shader_program;

  glm::vec3 pos, rot, scale;
  glm::mat4 model_matrix;
};



#endif
