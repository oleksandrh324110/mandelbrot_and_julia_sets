#pragma once

#include "includes.hpp"

namespace gfx {
class VBO {
 public:
  VBO();
  VBO(GLint type, bool dynamic);
  ~VBO();

  void bind() const;
  void buffer(void* data, size_t offset, size_t count) const;

 private:
  GLuint handle;
  GLint _type;
  bool _dynamic;
};
}  // namespace gfx