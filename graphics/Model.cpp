#include "Model.hpp"
#include <iostream>

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
                 GL_STATIC_DRAW);

    const int POSITION_INDEX = 0; // TODO: Fix dynamic index assignment by program.
    const int NUMBER_OF_ELEMENTS = 3;
    const int TYPE = GL_FLOAT;
    const bool NORMALIZATION = GL_FALSE;
    const int STRIDE_STEPS = 0;
    const void* BUFFER_OFFSET = 0;
    glVertexAttribPointer(POSITION_INDEX, 
                          NUMBER_OF_ELEMENTS, 
                          TYPE, 
                          NORMALIZATION, 
                          STRIDE_STEPS, 
                          BUFFER_OFFSET);
    buffers_generated = true;
  } else {
    // TODO: Throw exception!
  }
}

GLuint Model::getVertexArrayObject() const {
  if(buffers_generated) {
    return vertex_array_object;
  } else {
    // TODO: Throw exception!
  }
}

GLuint Model::getVertexBufferObject() const {
  if(buffers_generated) {
    return vertex_buffer_object;
  } else {
    // TODO: Throw exception!
  }
}

int Model::getNumberVertices() const {
  return vertices.size();
}

void Model::addFace(Face* face) {
  faces.push_back(*face);

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
