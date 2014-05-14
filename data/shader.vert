#version 330
in vec3 position;
in vec3 normal;
in vec2 texture_cords;
//in vec3 color;
uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 proj_mat;
//out vec3 Color;
out vec3 Normal;
out vec2 TextureCords;
void main() {
  //Color = normal;
  TextureCords = texture_cords;
  Normal = ( model_mat * vec4(normal, 0.0) ).xyz;
  gl_Position = proj_mat * view_mat * model_mat * vec4(position, 1.0);
}

