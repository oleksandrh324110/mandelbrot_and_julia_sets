#pragma once

#include <glad/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
 public:
  GLuint _id;

  Shader(const char* vs_path, const char* fs_path);
  void use() const;
  void setBool(const char* name, GLboolean value) const;
  void setInt(const char* name, GLint value) const;
  void setFloat(const char* name, GLfloat value) const;
};