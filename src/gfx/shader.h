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
void shader_uniform_float(Shader self, const char* name, GLfloat f);
void shader_uniform_vec2(Shader self, const char* name, vec2s v);
void shader_uniform_vec3(Shader self, const char* name, vec3s v);
void shader_uniform_vec4(Shader self, const char* name, vec4s v);
void shader_uniform_int(Shader self, const char* name, GLint v);
void shader_uniform_uint(Shader self, const char* name, GLuint v);
