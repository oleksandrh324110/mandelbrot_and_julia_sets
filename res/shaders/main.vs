#version 330 core

in vec3 aPos;

uniform vec2 offset;

void main() {
  gl_Position = vec4(aPos + vec3(offset / 20, 0), 1);
}
