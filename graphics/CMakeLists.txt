
cmake_minimum_required( VERSION 2.8)

project(dark CXX)

set(SRCS 
    GraphicsEngine.cpp 
    Scene.cpp 
    Shader.cpp 
    ShaderProgram.cpp 
    Model.cpp 
    AssImporter.cpp 
    Camera.cpp
    Texture.cpp
    main.cpp)


set(CFLAGS -Wall -std=c++1y -stdlib=libc++ -Wno-extra-tokens -O0 -g)
add_compile_options(${CFLAGS})

add_executable(dark ${SRCS})

set(LIBS
    glfw3
    boost_filesystem
    boost_system
    assimp
    freeimageplus
    Cocoa
    OpenGL)

  #foreach (LIB ${LIBS})
  #  find_library(${LIB}_LIBRARY ${LIB})
  #  if(NOT ${LIB}_LIBRARY)
  #    target_link_libraries(dark ${LIB}_LIBRARY)
  #  endif(NOT ${LIB}_LIBRARY)
  #endforeach(LIB)


#foreach(LIB ${LIBS})
#  set(LIB_PATH)
#  find_library(LIB_PATH ${LIB})
#  message("${LIB_PATH}")
#  target_link_libraries(dark ${LIB_PATH})
#  set(LIB_PATH)
#endforeach(LIB)

set(CMAKE_FIND_STATIC FIRST)

find_library(GLFW3_PATH glfw3)
target_link_libraries(dark ${GLFW3_PATH})

find_library(FILE_PATH boost_filesystem)
target_link_libraries(dark ${FILE_PATH})

find_library(SYSTEM_PATH boost_system)
target_link_libraries(dark ${SYSTEM_PATH})

find_library(ASSIMP_PATH assimp)
target_link_libraries(dark ${ASSIMP_PATH})

find_library(FREEIMAGE_PATH freeimageplus)
target_link_libraries(dark ${FREEIMAGE_PATH})

find_library(COCOA_PATH Cocoa)
target_link_libraries(dark ${COCOA_PATH})

find_library(OPENGL_PATH OpenGL)
target_link_libraries(dark ${OPENGL_PATH})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# include_directories(dir1 dir2 ...)

# link_directories(dir1 dir2 ...)

# find_package

# find_library

# message(msg)

# target_link_libraries
