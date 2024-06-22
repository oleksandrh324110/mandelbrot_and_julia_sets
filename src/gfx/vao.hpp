#pragma once

#include "../App.hpp"
#include "../util/util.hpp"
#include "gfx.hpp"
#include "vbo.hpp"

namespace gfx {
class VAO {
 public:
  VAO();
  ~VAO();

  void bind() const;
  void attr(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride,
            size_t offset) const;

 private:
  GLuint _handle;
};
};  // namespace gfx