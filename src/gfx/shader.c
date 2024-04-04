#include "shader.h"

static void _log_and_fail(
  GLint handle, const char* adverb, const char* path,
  void (*getlog)(GLuint, GLsizei, GLsizei*, GLchar*),
  void (*getiv)(GLuint, GLenum, GLint*))
{
  GLint loglen;
  getiv(handle, GL_INFO_LOG_LENGTH, &loglen);

  char* logtext = malloc(loglen);
  getlog(handle, loglen, NULL, logtext);
  fprintf(stderr, "Error %s shader at %s:\n%s", adverb, path, logtext);

  free(logtext);
  exit(1);
}

static GLint _compile(const char* path, GLenum type) {
  FILE* f;
  char* text;
  size_t len;

  f = fopen(path, "r");
  if (f == NULL) {
    fprintf(stderr, "Error loading shader at %s\n", path);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  len = ftell(f);
  assert(len > 0);
  fseek(f, 0, SEEK_SET);
  text = malloc(len);
  assert(text != NULL);
  fread(text, 1, len, f);
  assert(strlen(text) > 0);
  fclose(f);

  GLuint handle = glCreateShader(type);
  glShaderSource(handle, 1, (const GLchar* const*)&text, (const GLint*)&len);
  glCompileShader(handle);

  GLint compiled;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

  if (compiled == 0)
    _log_and_fail(handle, "compiling", path, glGetShaderInfoLog, glGetShaderiv);

  free(text);
  return handle;
}

Shader shader_create(const char* vs_path, const char* fs_path, size_t n, VertexAttrib attributes[]) {
  Shader self;
  GLuint vs_handle = _compile(vs_path, GL_VERTEX_SHADER);
  GLuint fs_handle = _compile(fs_path, GL_FRAGMENT_SHADER);
  self.handle = glCreateProgram();

  glAttachShader(self.handle, vs_handle);
  glAttachShader(self.handle, fs_handle);

  for (size_t i = 0; i < n; i++)
    glBindAttribLocation(self.handle, attributes[i].index, attributes[i].name);

  glLinkProgram(self.handle);

  GLint linked;
  glGetProgramiv(self.handle, GL_LINK_STATUS, &linked);

  if (linked == 0) {
    char buf[512];
    snprintf(buf, 512, "[%s, %s]", vs_path, fs_path);
    _log_and_fail(self.handle, "linking", buf, glGetProgramInfoLog, glGetProgramiv);
  }

  glDeleteShader(vs_handle);
  glDeleteShader(fs_handle);

  return self;
}

void shader_destroy(Shader self) {
  glDeleteProgram(self.handle);
}

void shader_bind(Shader self) {
  glUseProgram(self.handle);
}

void shader_uniform_float(Shader self, char* name, float f) {
  glUniform1f(glGetUniformLocation(self.handle, name), f);
}

void shader_uniform_vec2(Shader self, char* name, vec2s v) {
  glUniform2f(glGetUniformLocation(self.handle, name), v.x, v.y);
}

void shader_uniform_vec3(Shader self, char* name, vec3s v) {
  glUniform3f(glGetUniformLocation(self.handle, name), v.x, v.y, v.z);
}

void shader_uniform_vec4(Shader self, char* name, vec4s v) {
  glUniform4f(glGetUniformLocation(self.handle, name), v.x, v.y, v.z, v.w);
}

void shader_uniform_int(Shader self, char* name, int v) {
  glUniform1i(glGetUniformLocation(self.handle, name), v);
}
void shader_uniform_uint(Shader self, char* name, unsigned int v) {
  glUniform1ui(glGetUniformLocation(self.handle, name), v);
}