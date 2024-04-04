#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct {
  GLuint index;
  const GLchar* name;
} VertexAttrib;

typedef struct {
  GLuint handle;
} Shader;

Shader shader_create(const char* vs_path, const char* fs_path, size_t n, VertexAttrib attributes[]);
void shader_destroy(Shader self);
void shader_bind(Shader self);
void shader_uniform_float(Shader self, char* name, float f);
void shader_uniform_vec2(Shader self, char* name, vec2s v);
void shader_uniform_vec3(Shader self, char* name, vec3s v);
void shader_uniform_vec4(Shader self, char* name, vec4s v);
void shader_uniform_int(Shader self, char* name, int v);
void shader_uniform_uint(Shader self, char* name, unsigned int v);
