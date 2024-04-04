#pragma once

#include "../util/util.h"
#include "gfx.h"

typedef struct {
  GLuint handle;
  GLint target;
  bool dynamic;
} VBO;

VBO vbo_create(GLint type, bool dynamic);
void vbo_destroy(VBO self);
void vbo_bind(VBO self);
void vbo_buffer(VBO self, void* data, size_t offset, size_t size);