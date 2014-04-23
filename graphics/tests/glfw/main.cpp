#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glfw.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace glm;

int running = GL_TRUE;

float vertices[] = {
   0.0f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,

   0.25f,  0.5f, 0.5f,
   0.75f, -0.5f, 0.5f,
  -0.25f, -0.5f, 0.5f
};

GLuint vao;
GLuint vbo;
GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;

vec3 pos = vec3(0.0f, 0.0f, 2.0f);
vec3 dir = vec3(0.0f, 0.0f, -1.0f);
vec3 up = vec3(0.0f, 1.0f, 0.0f);

mat4 model_mat;
GLint model_loc;
mat4 view_mat;
GLint view_loc;
mat4 proj_mat;
GLint proj_loc;


void openWindow(int width, int height) {

  if( !glfwOpenWindow(width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
  {
    glfwTerminate();
    return;
  }

  // Call after window has been opened.
  glfwSetWindowTitle("GLFW test");

  glfwDisable(GLFW_MOUSE_CURSOR);
}

void init() {
  
  if( !glfwInit() ) {
    return;
  }
  
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLuint loadShader(string file) {

  // Find shader type
  string ext = file.substr(file.find_last_of(".") + 1);
  GLenum type;
  if(boost::algorithm::iequals(ext, "vert")) {
    type = GL_VERTEX_SHADER;
  } else if(boost::algorithm::iequals(ext, "frag")) {
    type = GL_FRAGMENT_SHADER;
  } else {
    // TODO: Error handling!
  }

  // Load source code
  ifstream shaderFile(file);
  stringstream buffer;
  buffer << shaderFile.rdbuf();
  const char* source = buffer.str().c_str();

  // Create and compile
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint status = GL_TRUE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(status == GL_FALSE) {
    cout << "Compile error in file: " << file << endl;
    char log[1024];
    GLsizei length = 0;
    glGetShaderInfoLog(shader, 1024, &length, log);
    cout << log << endl;
  }

  return shader;

}
void setup() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  vertexShader = loadShader("shader.vert");
  fragmentShader = loadShader("shader.frag");

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  // Bind output to (default) buffer
  glBindFragDataLocation(shaderProgram, 0, "outColor");

  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Link attributes
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);

  // Link uniforms
  GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
  glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

  model_loc = glGetUniformLocation(shaderProgram, "model_mat");
  view_loc = glGetUniformLocation(shaderProgram, "view_mat");
  proj_loc = glGetUniformLocation(shaderProgram, "proj_mat");
  
  model_mat = mat4();
  view_mat = lookAt(pos, pos + dir, up);
  proj_mat = perspective(45.0f, (600.0f/400.0f), 0.1f, 100.0f);

  glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(model_mat));
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(view_mat));
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, value_ptr(proj_mat));

  
}

double prev_time = 0;

void run() {

  float delta = 0;
  int prev_x, prev_y;
  glfwGetMousePos(&prev_x, &prev_y);
  while(running) {

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT );

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers();
    double time = glfwGetTime();
    delta = double(time - prev_time);
    prev_time = time;

    //////////// UPDATE SHIT //////////////

    // Movement
    float speed = 1.0f;
    if(glfwGetKey('D') == GLFW_PRESS) {
      pos += normalize(cross(dir, up)) * speed * delta;
    }
    if(glfwGetKey('A') == GLFW_PRESS) {
      pos += -normalize(cross(dir, up)) * speed * delta;
    }
    if(glfwGetKey('W') == GLFW_PRESS) {
      pos += dir * speed * delta;
    }
    if(glfwGetKey('S') == GLFW_PRESS) {
      pos += -dir * speed * delta;
    }

    // Mouse
    float mouse_sens = 0.1f;
    int x, y;
    glfwGetMousePos(&x, &y);
    float delta_x = float(x - prev_x) * mouse_sens;
    float delta_y = float(y - prev_y) * mouse_sens;
    prev_x = x; prev_y = y;

    dir = rotateY(dir, -delta_x);
    dir = rotate(dir, -delta_y, cross(dir, up));

    view_mat = lookAt(pos, pos + dir, up);
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(view_mat));

    // Exit stuff
    running = !glfwGetKey( GLFW_KEY_ESC ) &&
          glfwGetWindowParam( GLFW_OPENED );
  }

}

int main(void) {
  
  init();
  openWindow(600, 400);
  setup();

  cout<<"OpenGL version = "<<glGetString(GL_VERSION)<<endl;

  run();

  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);

  glfwTerminate();


  return 0;
}






