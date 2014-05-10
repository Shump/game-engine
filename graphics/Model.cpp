#include "Model.hpp"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Model::Model(vector<Face> _faces, 
             vector<float> _vertices, 
             vector<float> _colors, 
             shared_ptr<ShaderProgram> shader_program) : 
               faces(_faces), vertices(_vertices), colors(_colors) {
  // TODO: Explore move semantics
  Model::shader_program = shader_program;
  setupGPU();
}

Model::~Model() {
  if(buffers_generated) {
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteVertexArrays(1, &vertex_array_object);
  }
  //for(Face* face : faces) {
    //delete face;
  //}
  //faces.clear();
}

void Model::setupGPU() {
  // TODO: Make uploading to GPU optional!
  // TODO: RAII Resource allocation is initialization
  if(!buffers_generated) {
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

    glBufferData(GL_ARRAY_BUFFER, 
                 vertices.size() * sizeof(float), 
                 vertices.data(), 
                 GL_STATIC_DRAW); // TODO: Allow for DYNAMIC_DRAW and STREAM_DRAW

    
    const int POSITION_INDEX = 0; // TODO: Fix dynamic index assignment by program. This is hardcoded for the "position" input in the vertex shader.
    const int NUMBER_OF_ELEMENTS = 3;
    const int TYPE = GL_FLOAT;
    const bool NORMALIZATION = GL_FALSE;
    const int STRIDE_STEPS = 0;
    const void* BUFFER_OFFSET = 0;
    glEnableVertexAttribArray(POSITION_INDEX);
    glVertexAttribPointer(POSITION_INDEX,
                          NUMBER_OF_ELEMENTS, 
                          TYPE, 
                          NORMALIZATION, 
                          STRIDE_STEPS, 
                          BUFFER_OFFSET);
    buffers_generated = true;

    glBindVertexArray(0);
  }
}

GLuint Model::getVertexArrayObject() const {
  if(buffers_generated) {
    return vertex_array_object;
  } else {
    throw std::runtime_error("Model::getVertexArrayObject: vertex array object is not genereated for the model!");
  }
}

GLuint Model::getVertexBufferObject() const {
  if(buffers_generated) {
    return vertex_buffer_object;
  } else {
    throw std::runtime_error("Model::getVertexArrayObject: vertex buffer object is not genereated for the model!");
  }
}

int Model::getNumberVertices() const {
  return vertices.size();
}

void Model::addFace(Face* face) {
  faces.push_back(*face);

  // TODO: Optimize, clean-up
  for(int vertex = 0; vertex < 3; vertex++) {
    for(int component = 0; component < 3; component++) {
      vertices.push_back( (*face)[vertex][component] );
    }
  }
}

std::string Model::toString() const {
  std::string buffer = "Faces: {\n";
  for(const auto face : faces) {
    buffer += face.toString() + ",\n";
  }
  buffer += "}\n";
  return buffer;
}

void Model::setPosition(const glm::vec3& pos) {
  Model::pos = pos;
  updateModelMatrix();
}
void Model::setRotation(const glm::vec3& rot) {
  Model::rot = rot;
  updateModelMatrix();
}
void Model::setScale(const glm::vec3& scale) {
  Model::scale = scale;
  updateModelMatrix();
}
void Model::setTransformation(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) {
  Model::pos = pos;
  Model::rot = rot;
  Model::scale = scale;
  updateModelMatrix();
}


void Model::rotate(const float angle, const glm::vec3& axis) {
  model_matrix = glm::rotate(model_matrix, angle, axis);
}

void Model::updateModelMatrix() {
  model_matrix = glm::mat4();
  glm::rotate(model_matrix, rot.x, glm::vec3(1.0, 0.0, 0.0));
  glm::rotate(model_matrix, rot.y, glm::vec3(0.0, 1.0, 0.0));
  glm::rotate(model_matrix, rot.z, glm::vec3(0.0, 0.0, 1.0));

  glm::scale(model_matrix, scale);

  glm::translate(model_matrix, pos);
}

const glm::mat4& Model::getModelMatrix() const {
  return model_matrix;
}


