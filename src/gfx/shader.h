#pragma once

#include <glad/gl.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
 public:
  GLuint _id;

  Shader(const char* vs_path, const char* fs_path);
  void use() const;

  void set_bool(const char* name, GLboolean value) const;
  void set_int(const char* name, GLint value) const;
  void set_float(const char* name, GLfloat value) const;
  void set_vec2(const char* name, glm::vec2 vec) const;
  void set_ivec2(const char* name, glm::ivec2 vec) const;
};