
#version 330
in vec3 Normal;
uniform vec3 triangleColor;

uniform vec3 ambient_color;
uniform float ambient_intensity;

uniform vec3 sun_color;
uniform float sun_intensity;
uniform vec3 sun_dir;

out vec4 outColor;
void main() {
  vec4 ambient_light = vec4(ambient_color, 1.0) * ambient_intensity;
  float diffuse_sun_factor = (dot(Normal, sun_dir));
  diffuse_sun_factor = max(diffuse_sun_factor, 0.0);

  vec4 diffuse_light = vec4(sun_color, 0.0) * sun_intensity * diffuse_sun_factor;
  outColor = vec4(triangleColor, 1.0) * (ambient_light + diffuse_light);
}
