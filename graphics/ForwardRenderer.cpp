
#include "ForwardRenderer.hpp"

#include "Scene.hpp"
#include "Model.hpp"
#include "ShaderProgram.hpp"

#include "opengl.hpp"
#include "glm/glm.hpp"

ForwardRenderer::ForwardRenderer(const ShaderProgram& program) : program(program) {
}

ForwardRenderer::ForwardRenderer(ShaderProgram&& program) : program(std::move(program)) {
}

void ForwardRenderer::render(const Scene& scene) {

  //view_mat = scene.getConstCamera().getViewMatrix();

  for(const auto& model : scene.models) {
    render(model);
  }

}

void ForwardRenderer::render(const Model& model) {

  glBindVertexArray(model.getVertexArrayObject());
  glBindBuffer(GL_ARRAY_BUFFER, model.getVerticesVBO());

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, model.getTexture().getTextureId());

  program.setUniform("model_mat", model.getModelMatrix());
  //program.setUniform("view_mat", view_mat);
  //program.setUniform("proj_mat", proj_matrix);
  program.setUniform("triangleColor", glm::vec3(0.0, 1.0, 0.0));

  program.setUniform("ambient_color", glm::vec3(7.0f, 7.0, 1.0));
  program.setUniform("ambient_intensity", 0.1f);
  program.setUniform("sun_dir", glm::vec3(1.0f, 1.0f, 1.0f));
  program.setUniform("sun_color", glm::vec3(1.0f, 1.0f, 1.0f));
  program.setUniform("sun_intensity", 1.0);
  glDrawArrays(GL_TRIANGLES, 0, model.getNumberVertices());

}
