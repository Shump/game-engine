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
    glDeleteBuffers(1, &vertices_vbo);
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

    setupVertices();
    setupNormals();

    buffers_generated = true;
    glBindVertexArray(0); // Bind to unassigned vao
  }
}

template<int elements>
void Model::setupVBO(GLuint* buffer, std::vector<float>* vector, 
                     int position_index) {
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);

    glBufferData(GL_ARRAY_BUFFER, 
                 vector->size() * sizeof(float), 
                 vector->data(), 
                 GL_STATIC_DRAW); // TODO: Allow for DYNAMIC_DRAW and STREAM_DRAW

    
    const int type = GL_FLOAT;
    const bool normalization = GL_FALSE;
    const int stride_steps = 0;
    const void* buffer_offset = 0;
    glEnableVertexAttribArray(position_index);
    glVertexAttribPointer(position_index,
                          elements, 
                          type, 
                          normalization, 
                          stride_steps, 
                          buffer_offset);

}

void Model::setupVertices() {
    glGenBuffers(1, &vertices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

    glBufferData(GL_ARRAY_BUFFER, 
                 vertices.size() * sizeof(float), 
                 vertices.data(), 
                 GL_STATIC_DRAW); // TODO: Allow for DYNAMIC_DRAW and STREAM_DRAW

    
    const int position_index = 0; // TODO: Fix dynamic index assignment by program. This is hardcoded for the "position" input in the vertex shader.
    const int number_of_elements = 3;
    const int type = GL_FLOAT;
    const bool normalization = GL_FALSE;
    const int stride_steps = 0;
    const void* buffer_offset = 0;
    glEnableVertexAttribArray(position_index);
    glVertexAttribPointer(position_index,
                          number_of_elements, 
                          type, 
                          normalization, 
                          stride_steps, 
                          buffer_offset);
}

void Model::setupNormals() {
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);

    glBufferData(GL_ARRAY_BUFFER, 
                 normals.size() * sizeof(float), 
                 normals.data(), 
                 GL_STATIC_DRAW); // TODO: Allow for DYNAMIC_DRAW and STREAM_DRAW

    
    const int position_index = 1; // TODO: Fix dynamic index assignment by program. This is hardcoded for the "position" input in the vertex shader.
    const int number_of_elements = 3;
    const int type = GL_FLOAT;
    const bool normalization = GL_FALSE;
    const int stride_steps = 0;
    const void* buffer_offset = 0;
    glEnableVertexAttribArray(position_index);
    glVertexAttribPointer(position_index,
                          number_of_elements, 
                          type, 
                          normalization, 
                          stride_steps, 
                          buffer_offset);


}

GLuint Model::getVertexArrayObject() const {
  if(buffers_generated) {
    return vertex_array_object;
  } else {
    throw std::runtime_error("Model::getVertexArrayObject: vertex array object is not genereated for the model!");
  }
}

GLuint Model::getVerticesVBO() const {
  if(buffers_generated) {
    return vertices_vbo;
  } else {
    throw std::runtime_error("Model::getVerticesVBO: vertex buffer object is not genereated for the vertices in the model!");
  }
}

GLuint Model::getNormalsVBO() const {
  if(buffers_generated) {
    return normals_vbo;
  } else {
    throw std::runtime_error("Model::getNormalsVBO: vertex buffer object is not genereated for the normals in the model!");
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
      normals.push_back( (*face).normals[vertex][component] );
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


