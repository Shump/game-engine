#ifndef MODEL_HPP
#define MODEL_HPP

#include "opengl.hpp"
#include "ShaderProgram.hpp"
#include "Face.hpp"

#include <memory>
#include <vector>
#include <string>

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


private:
  bool buffers_generated = false;

  std::vector<Face> faces;
  std::vector<float> vertices;
  std::vector<float> colors;
  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
  std::shared_ptr<ShaderProgram> shader_program;


};



#endif MODEL_HPP
