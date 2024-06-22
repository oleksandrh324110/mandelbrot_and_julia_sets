#pragma once

#include "../App.hpp"
#include "../util/util.hpp"
#include "gfx.hpp"

namespace gfx {
class VBO {
 public:
  VBO(GLint type, bool dynamic);
  ~VBO();

  void bind() const;
  void buffer(void* data, size_t offset, size_t count) const;

 private:
  GLuint _handle;
  GLint _type;
  bool _dynamic;
};
}  // namespace gfx