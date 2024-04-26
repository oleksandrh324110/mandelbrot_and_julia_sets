#pragma once

#include "../util/util.h"
#include "gfx.h"

typedef struct {
  GLuint handle;
  GLenum target;
  GLenum usage;
} VBO;

VBO vbo_create(GLenum type, GLenum usage);
void vbo_destroy(VBO self);
void vbo_bind(VBO self);
void vbo_buffer(VBO self, GLsizeiptr size, const GLvoid* data);
