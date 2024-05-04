#version 330 core

in vec3 aPos;

out vec2 coords;

void main() {
  gl_Position = vec4(aPos, 1);
  coords = aPos.xy;
}
