#include "vao.h"

VAO vao_create(void) {
  VAO self;
  glGenVertexArrays(1, &self.handle);
  return self;
}

void vao_destroy(VAO self) {
  glDeleteVertexArrays(1, &self.handle);
}

void vao_bind(VAO self) {
  glBindVertexArray(self.handle);
}

void vao_attrib(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) {
  switch (type) {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
    case GL_INT:
    case GL_UNSIGNED_INT:
      glVertexAttribIPointer(index, size, type, stride, pointer);
      break;
    default:
      glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
      break;
  }
  glEnableVertexAttribArray(index);
}
