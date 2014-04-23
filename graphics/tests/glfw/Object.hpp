

#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glfw.h>
#include <string>

class Object {
public:
  Object();

  GLuint vao;

  const string name;
  const float* vertices;
  const int*   indices;
  const float* normals;
  const float* uvs;
};

#endif
