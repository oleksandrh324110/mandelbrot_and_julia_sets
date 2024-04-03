#pragma once

#include "../util/util.h"
#include "gfx.h"

typedef struct {
  GLuint handle;
  GLint target;
  bool dynamic;
} vbo;

vbo vbo_create(GLint type, bool dynamic);
void vbo_destroy(vbo self);
void vbo_bind(vbo self);
void vbo_buffer(vbo self, void* data, size_t offset, size_t size);