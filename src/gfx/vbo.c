#include "vbo.h"

VBO vbo_create(GLenum target, GLenum usage) {
  VBO self = {.target = target, .usage = usage};
  glGenBuffers(1, &self.handle);
  return self;
}

void vbo_destroy(VBO self) {
  glDeleteBuffers(1, &self.handle);
}

void vbo_bind(VBO self) {
  glBindBuffer(self.target, self.handle);
}

void vbo_buffer(VBO self, GLsizeiptr size, const GLvoid* data) {
  glBufferData(self.target, size, data, self.usage);
}
