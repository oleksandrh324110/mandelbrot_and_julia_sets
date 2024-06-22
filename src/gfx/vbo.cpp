#include "vbo.hpp"

namespace app {
VBO::VBO(GLint type, bool dynamic) : type(type), dynamic(dynamic) {
  glGenBuffers(1, &handle);
}

VBO::~VBO() { glDeleteBuffers(1, &handle); }

void VBO::bind() const { glBindBuffer(type, handle); }

void VBO::buffer(void* data, size_t offset, size_t count) const {
  if (dynamic) {
    glBufferSubData(type, offset, count, data);
  } else {
    glBufferData(type, count, data, GL_STATIC_DRAW);
  }
}
}  // namespace app