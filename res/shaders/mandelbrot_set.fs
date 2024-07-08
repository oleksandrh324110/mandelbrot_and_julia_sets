#version 330 core

uniform float color;

out vec4 FragColor;

void main() {
  FragColor = vec4(vec3(color), 1);
}
