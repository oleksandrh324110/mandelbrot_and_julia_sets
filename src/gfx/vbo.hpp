#pragma once

#include "../utils/utils.hpp"

namespace gfx {
class VBO {
 public:
  GLuint handle;
  GLint type;
  bool dynamic;

  VBO(GLint type, bool dynamic);
  ~VBO();

  void bind() const;
  void buffer(void* data, size_t offset, size_t count) const;
};
}  // namespace gfx