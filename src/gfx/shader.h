#pragma once

#include "../util/util.h"
#include "gfx.h"

typedef struct {
  GLuint index;
  const GLchar* name;
} VertexAttr;

typedef struct {
  GLuint handle;
} Shader;

Shader shader_create(const char* vs_path, const char* fs_path, size_t n, VertexAttr attributes[]);
void shader_destroy(Shader self);
void shader_bind(Shader self);
void shader_use(Shader self);
