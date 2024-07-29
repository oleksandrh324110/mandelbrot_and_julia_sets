#include "vao.hpp"

VAO::VAO() {
  glGenVertexArrays(1, &handle);
  bind();
}
VAO::~VAO() { glDeleteVertexArrays(1, &handle); }
void VAO::bind() const { glBindVertexArray(handle); }
void VAO::set_attrib(VBO &vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) const {
  bind();
  vbo.bind();

  switch (type) {
  case GL_BYTE:
  case GL_UNSIGNED_BYTE:
  case GL_SHORT:
  case GL_UNSIGNED_SHORT:
  case GL_INT:
  case GL_UNSIGNED_INT:
  case GL_INT_2_10_10_10_REV:
  case GL_UNSIGNED_INT_2_10_10_10_REV:
    glVertexAttribIPointer(index, size, type, stride, (void *)offset);
    break;
  default:
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
    break;
  }
  glEnableVertexAttribArray(index);
}
