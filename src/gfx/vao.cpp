#include "vao.hpp"

namespace gfx {
VAO::VAO() { glGenVertexArrays(1, &_handle); }
VAO::~VAO() { glDeleteVertexArrays(1, &_handle); }
void VAO::bind() const { glBindVertexArray(_handle); }
void VAO::attr(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride,
               size_t offset) const {
  vbo.bind();
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(index);
}
}  // namespace gfx