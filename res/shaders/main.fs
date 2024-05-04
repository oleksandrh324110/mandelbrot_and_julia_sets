#version 330 core

uniform vec2 resolution;
uniform vec2 scroll;
uniform float zoom;

in vec2 coords;

out vec4 color;

const int MAX_ITERATIONS = 64;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main() {
  float aspect = resolution.x / resolution.y;
  float scrollX = scroll.x / 2 / aspect;
  float scrollY = scroll.y / 2;

  float xFrom = -2 + scrollX;
  float xTo = 2 + scrollX;
  float yFrom = -2 + scrollY;
  float yTo = 2 + scrollY;

  float a = map(coords.x, -1, 1, xFrom, xTo) * aspect;
  float b = map(coords.y, -1, 1, yFrom, yTo);

  float ca = a;
  float cb = b;

  int n = 0;
  for (; n < MAX_ITERATIONS; n++) {
    float aa = a * a - b * b;
    float bb = 2 * a * b;

    if (aa * aa + bb * bb > 100) {
      break;
    }

    a = aa + ca;
    b = bb + cb;
  }

  float brightness = float(n) / float(MAX_ITERATIONS);
  if (n == MAX_ITERATIONS)
    brightness = 0;
  color = vec4(brightness, brightness, brightness, 1);
}
