#pragma once

#include "../util/util.h"
#include "gfx.h"

typedef struct {
  GLuint handle;
} Shader;

Shader shader_create(const char* vs_path, const char* fs_path);
void shader_destroy(Shader self);
void shader_bind(Shader self);
void shader_uniform1i(Shader self, const char* name, int value);
void shader_uniform1f(Shader self, const char* name, float value);
void shader_uniform2f(Shader self, const char* name, float x, float y);
void shader_uniform3f(Shader self, const char* name, float x, float y, float z);
void shader_uniform4f(Shader self, const char* name, float x, float y, float z, float w);
