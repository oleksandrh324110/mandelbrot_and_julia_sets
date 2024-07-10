#version 330 core

uniform vec2 resolution;
uniform vec2 top_left;
uniform vec2 bottom_right;
uniform float hue_shift;
uniform int max_iterations;
uniform float pow;

out vec4 FragColor;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

vec3 hsv2rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec2 complex_pow(vec2 z, float n) {
  float r = length(z); // Magnitude of the complex number
  float theta = atan(z.y, z.x); // Angle of the complex number

  float new_r = exp(n * log(r)); // Apply power to the magnitude using exp and log
  float new_theta = theta * n; // Apply power to the angle

  // Convert back to Cartesian coordinates
  return vec2(new_r * cos(new_theta), new_r * sin(new_theta));
}

void main() {
  vec2 z = vec2(
    map(gl_FragCoord.x, 0, resolution.x, top_left.x, bottom_right.x),
    map(gl_FragCoord.y, 0, resolution.y, top_left.y, bottom_right.y)
  );
  vec2 c = z;

  float i;
  for (i = 0; i < max_iterations; i++) {
    z = complex_pow(z, pow) + c;
    if (length(z) > 16)
      break;
  }

  if (i >= max_iterations)
    FragColor = vec4(0, 0, 0, 1);
  else {
    vec3 color = hsv2rgb(vec3(i / max_iterations + hue_shift, 1, 1));
    FragColor = vec4(color, 1);
  }

  int x = int(gl_FragCoord.x);
  int y = int(gl_FragCoord.y);
  int middle_x = int(resolution.x / 2);
  int middle_y = int(resolution.y / 2);

  if (x == middle_x && y >= middle_y - 10 && y <= middle_y + 10 || y == middle_y && x >= middle_x - 10 && x <= middle_x + 10)
    FragColor = vec4(1, 1, 1, 1);
}
