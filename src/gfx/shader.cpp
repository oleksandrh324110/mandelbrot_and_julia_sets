#include "shader.h"

Shader::Shader(const char* vs_path, const char* fs_path) {
  std::string vs_code, fs_code;
  std::ifstream vs_file, fs_file;

  vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vs_file.open(vs_path);
    fs_file.open(fs_path);

    std::stringstream vs_stream, fs_stream;

    vs_stream << vs_file.rdbuf();
    fs_stream << fs_file.rdbuf();

    vs_file.close();
    fs_file.close();

    vs_code = vs_stream.str();
    fs_code = fs_stream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << e.what()
              << std::endl;
  }

  GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* vs_char_code = vs_code.c_str();
  const GLchar* fs_char_code = fs_code.c_str();
  glShaderSource(vs_id, 1, &vs_char_code, nullptr);
  glShaderSource(fs_id, 1, &fs_char_code, nullptr);

  GLint success;
  glGetShaderiv(vs_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(vs_id, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << info_log << std::endl;
  }
  glGetShaderiv(fs_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint log_length;
    glGetShaderiv(fs_id, GL_INFO_LOG_LENGTH, &log_length);
    char log_info[log_length];
    glGetShaderInfoLog(fs_id, log_length, NULL, log_info);

    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << log_info << std::endl;
  }

  _id = glCreateProgram();
  glAttachShader(_id, vs_id);
  glAttachShader(_id, fs_id);
  glLinkProgram(_id);

  glGetShaderiv(_id, GL_LINK_STATUS, &success);
  if (!success) {
    GLint log_length;
    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &log_length);
    char log_info[log_length];
    glGetProgramInfoLog(_id, log_length, NULL, log_info);

    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << log_info << std::endl;
  }

  glDeleteShader(vs_id);
  glDeleteShader(fs_id);
}

void Shader::use() const { glUseProgram(_id); }
void Shader::setBool(const char* name, GLboolean value) const {
  glUniform1i(glGetUniformLocation(_id, name), (int)value);
}
void Shader::setInt(const char* name, GLint value) const {
  glUniform1i(glGetUniformLocation(_id, name), value);
}
void Shader::setFloat(const char* name, GLfloat value) const {
  glUniform1f(glGetUniformLocation(_id, name), value);
}