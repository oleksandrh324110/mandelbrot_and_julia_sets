#include "vbo.hpp"

namespace gfx {
VBO::VBO() {}
VBO::VBO(GLint type, bool dynamic) : _type(type), _dynamic(dynamic) { glGenBuffers(1, &handle); }
VBO::~VBO() { glDeleteBuffers(1, &handle); }

void VBO::bind() const { glBindBuffer(_type, handle); }

void VBO::buffer(void* data, size_t offset, size_t count) const {
  if (_dynamic) {
    glBufferSubData(_type, offset, count, data);
  } else {
    glBufferData(_type, count, data, GL_STATIC_DRAW);
  }
}
}  // namespace gfx