#include "vbo.hpp"

VBO::VBO(GLint type, bool dynamic) : type(type), dynamic(dynamic) {
  glGenBuffers(1, &handle);
  bind();
}
// clang-format off
VBO::~VBO() { 
  glDeleteBuffers(1, &handle); 
}

void VBO::bind() const { glBindBuffer(type, handle); }

void VBO::set_data(void* data, size_t size) const {
  bind();
  glBufferData(type, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
