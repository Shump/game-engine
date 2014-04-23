#define GLFW_INCLUDE_GL3
//#define GLFW_NO_GLU
#include <iostream>
#include <GL/glfw.h>
#include <glm/glm.hpp>

using namespace std;

int main(void) {
  
  int running = GL_TRUE;

  if( !glfwInit() ) {
    return 1;
  }

  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(GL_GLEXT_LEGACY)
  cout << "apa" << endl;
#endif

  if( !glfwOpenWindow(300, 300, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
  {
    glfwTerminate();
    return 0;
  }

  cout<<"OpenGL version = "<<glGetString(GL_VERSION)<<endl;

  while(running) {
    glClear( GL_COLOR_BUFFER_BIT );

    glfwSwapBuffers();
    
    running = !glfwGetKey( GLFW_KEY_ESC ) &&
          glfwGetWindowParam( GLFW_OPENED );
  }

  glfwTerminate();


  return 0;
}






