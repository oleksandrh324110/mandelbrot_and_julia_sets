#pragma once

#include "../util/util.hpp"
#include "gfx.hpp"

class VBO {
 public:
  VBO(GLint type, bool dynamic);
  ~VBO();

  void bind() const;
  void buffer(void* data, size_t offset, size_t count) const;

 private:
  GLuint handle;
  GLint type;
  bool dynamic;
};
