#version 150
in vec3 position;
in vec3 color;
uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 proj_mat;
out vec3 Color;
void main() {
  Color = color;
  gl_Position = proj_mat * view_mat * model_mat * vec4(position, 1.0);
}
