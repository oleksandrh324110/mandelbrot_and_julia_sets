#pragma once

#include "../util/util.h"
#include "gfx.h"

typedef struct {
  GLuint handle;
  GLenum type;
  bool dynamic : 1;
} VBO;

VBO vbo_create(GLenum type, bool dynamic);
void vbo_destroy(VBO self);
void vbo_bind(VBO self);
void vbo_data(VBO self, size_t size, void* data);
