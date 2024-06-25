#include "shader.hpp"

static void _compile_and_check(GLuint s_id, const char* description) {
  GLint success;
  glCompileShader(s_id);
  glGetShaderiv(s_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint info_log_length;
    glGetShaderiv(s_id, GL_INFO_LOG_LENGTH, &info_log_length);
    char info_log[info_log_length];
    glGetShaderInfoLog(s_id, info_log_length, NULL, info_log);
    std::cout << "ERROR::SHADER::" << description << "::COMPILATION_FAILED\n"
              << info_log << std::endl;
  }
}

namespace gfx {
Shader::Shader(const char* vs_path, const char* fs_path) {
  std::string vs_code, fs_code;
  std::ifstream vs_file, fs_file;

  vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vs_file.open(vs_path);
    std::stringstream vs_stream;
    vs_stream << vs_file.rdbuf();
    vs_file.close();
    vs_code = vs_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << vs_path << std::endl;
  }

  try {
    fs_file.open(fs_path);
    std::stringstream fs_stream;
    fs_stream << fs_file.rdbuf();
    fs_file.close();
    fs_code = fs_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << fs_path << std::endl;
  }

  GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);
  const char* vs_char_code = vs_code.c_str();
  const char* fs_char_code = fs_code.c_str();
  glShaderSource(vs_id, 1, &vs_char_code, nullptr);
  glShaderSource(fs_id, 1, &fs_char_code, nullptr);

  _compile_and_check(vs_id, "VERTEX");
  _compile_and_check(fs_id, "FRAGMENT");

  handle = glCreateProgram();
  glAttachShader(handle, vs_id);
  glAttachShader(handle, fs_id);
  glLinkProgram(handle);

  GLint success;
  glGetProgramiv(handle, GL_LINK_STATUS, &success);
  if (!success) {
    GLint log_length;
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    char log_info[log_length];
    glGetProgramInfoLog(handle, log_length, NULL, log_info);

    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log_info << std::endl;
  }

  glDeleteShader(vs_id);
  glDeleteShader(fs_id);
}

Shader::~Shader() { glDeleteProgram(handle); }

void Shader::use() const { glUseProgram(handle); }
void Shader::set_bool(const char* name, GLboolean value) const {
  glUniform1i(glGetUniformLocation(handle, name), (int)value);
}
void Shader::set_int(const char* name, GLint value) const {
  glUniform1i(glGetUniformLocation(handle, name), value);
}
void Shader::set_float(const char* name, GLfloat value) const {
  glUniform1f(glGetUniformLocation(handle, name), value);
}
void Shader::set_vec2(const char* name, glm::vec2 vec) const {
  glUniform2f(glGetUniformLocation(handle, name), vec.x, vec.y);
}
void Shader::set_ivec2(const char* name, glm::ivec2 vec) const {
  glUniform2i(glGetUniformLocation(handle, name), vec.x, vec.y);
}
}  // namespace gfx