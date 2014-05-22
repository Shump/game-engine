#ifndef UTILITY_HPP
#define UTILITY_HPP 

#include <assimp/matrix4x4.h>
#include <glm/mat4x4.hpp>

// Converts to column-major as opengl "prefers"
inline glm::mat4 toGlmMatrix(const aiMatrix4x4& ai_mat) {
  return glm::mat4(ai_mat.a1, ai_mat.b1, ai_mat.c1, ai_mat.d1,
                   ai_mat.a2, ai_mat.b2, ai_mat.c2, ai_mat.d2,
                   ai_mat.a3, ai_mat.b3, ai_mat.c3, ai_mat.d3,
                   ai_mat.a4, ai_mat.b4, ai_mat.c4, ai_mat.d4);
}



#endif /* UTILITY_HPP */
