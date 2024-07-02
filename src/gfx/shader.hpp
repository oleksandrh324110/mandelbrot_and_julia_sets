#pragma once

#include "../utils/utils.hpp"

class Shader {
 public:
  GLuint handle;

  Shader(std::string vs_path, std::string fs_path);
  ~Shader();

  void use() const;

  void set_bool(std::string name, GLboolean value) const;
  void set_int(std::string name, GLint value) const;
  void set_float(std::string name, GLfloat value) const;
  void set_vec2(std::string name, glm::vec2 vec) const;
  void set_ivec2(std::string name, glm::ivec2 vec) const;
};
