
cmake_minimum_required( VERSION 2.8)

project(dark CXX)

set(SRCS 
    GraphicsEngine.cpp 
    Scene.cpp 
    Shader.cpp 
    ShaderProgram.cpp 
    Model.cpp 
    AssImporter.cpp 
    main.cpp)


set(CFLAGS -Wall -std=c++11 -stdlib=libc++ -Wno-extra-tokens -O0 -g)
add_compile_options(${CFLAGS})

add_executable(dark ${SRCS})

set(LIBS
    glfw
    boost_filesystem
    boost_system
    assimp
    Cocoa
    OpenGL)

foreach(LIB ${LIBS})
  find_library(LIB_PATH ${LIB})
  target_link_libraries(dark ${LIB_PATH})
  unset(LIB_PATH)
endforeach(LIB)

message("${LINK_LIBRARIES}")


# include_directories(dir1 dir2 ...)

# link_directories(dir1 dir2 ...)

# find_package

# find_library

# message(msg)

# target_link_libraries
