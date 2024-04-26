#include "vbo.h"

VBO vbo_create(GLenum type, bool dynamic) {
  VBO self = {.type = type, .dynamic = dynamic};
  glGenBuffers(1, &self.handle);
  return self;
}

void vbo_destroy(VBO self) {
  glDeleteBuffers(1, &self.handle);
}

void vbo_bind(VBO self) {
  glBindBuffer(self.type, self.handle);
}

void vbo_data(VBO self, size_t size, void* data) {
  vbo_bind(self);
  glBufferData(self.handle, size, data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
