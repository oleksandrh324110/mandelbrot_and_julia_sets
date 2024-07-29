#pragma once

#include "../utils/utils.hpp"

class Shader {
public:
  GLuint handle;

  Shader();
  Shader(std::string_view vs_path, std::string_view fs_path);
  ~Shader();

  void use() const;

  void set_uniform(std::string_view name, GLboolean value) const;
  void set_uniform(std::string_view name, GLint value) const;
  void set_uniform(std::string_view name, GLfloat value) const;
  void set_uniform(std::string_view name, glm::vec2 vec) const;
  void set_uniform(std::string_view name, glm::ivec2 vec) const;
  void set_uniform(std::string_view name, glm::vec3 vec) const;
  void set_uniform(std::string_view name, glm::ivec3 vec) const;
  void set_uniform(std::string_view name, glm::vec4 vec) const;
  void set_uniform(std::string_view name, glm::ivec4 vec) const;
};
