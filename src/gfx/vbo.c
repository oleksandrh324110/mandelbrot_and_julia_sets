#include "vbo.h"

VBO vbo_create(GLint target, bool dynamic) {
  VBO self = {
    .target = target,
    .dynamic = dynamic
  };
  glGenBuffers(1, &self.handle);
  return self;
}

void vbo_destroy(VBO self) {
  glDeleteBuffers(1, &self.handle);
}

void vbo_bind(VBO self) {
  glBindBuffer(self.target, self.handle);
}

void vbo_buffer(VBO self, void* data, size_t offset, size_t size) {
  vbo_bind(self);
  glBufferData(self.target, size - offset, data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}