#pragma once

#include "../util/util.h"
#include "gfx.h"
#include "vbo.h"

typedef struct {
  GLuint handle;
} vao;

vao vao_create();
void vao_destroy(vao self);
void vao_bind(vao self);
void vao_attrib(vao self, vbo vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);