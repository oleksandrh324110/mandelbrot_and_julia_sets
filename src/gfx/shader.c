#include "shader.h"

static void _log_and_fail(
  GLuint handle, const char* adverb, const char* path,
  void(*getlog)(GLuint, GLsizei, GLsizei*, GLchar*),
  void(*getiv)(GLuint, GLenum, GLint*))
{
  GLint loglen;
  getiv(handle, GL_INFO_LOG_LENGTH, &loglen);
  char* logtext = malloc(loglen);
  getlog(handle, loglen, NULL, logtext);
  fprintf(stderr, "Error %s shader at %s:\n%s", adverb, path, logtext);
  free(logtext);
}

static GLuint _compile(const char* path, GLenum type) {
  FILE* f;
  char* text;
  size_t len;

  f = fopen(path, "r");
  if (!f) {
    fprintf(stderr, "Error loading shader at %s\n", path);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  len = ftell(f);
  if (!len) {
    fprintf(stderr, "Shader file is empty at %s\n", path);
    exit(1);
  }
  fseek(f, 0, SEEK_SET);
  text = malloc(len);
  assert(text != NULL);
  fread(text, 1, len, f);
  fclose(f);

  GLuint handle = glCreateShader(type);
  glShaderSource(handle, 1, (const GLchar* const*)&text, (const GLint*)&len);
  glCompileShader(handle);

  GLint compiled;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
    _log_and_fail(handle, "compiling", path, glGetShaderInfoLog, glGetShaderiv);

  free(text);
  return handle;
}

Shader shader_create(const char* vs_path, const char* fs_path, size_t n, VertexAttr attributes[]) {
  Shader self;

  self.handle = glCreateProgram();
  GLuint vs_handle = _compile(vs_path, GL_VERTEX_SHADER);
  GLuint fs_handle = _compile(fs_path, GL_FRAGMENT_SHADER);

  glAttachShader(self.handle, vs_handle);
  glAttachShader(self.handle, fs_handle);

  for (size_t i = 0; i < n; i++)
    glBindAttribLocation(self.handle, attributes[i].index, attributes[i].name);

  glLinkProgram(self.handle);

  GLint linked;
  glGetProgramiv(self.handle, GL_LINK_STATUS, &linked);
  if (!linked) {
    size_t len = strlen(vs_path) + strlen(fs_path) + 5;
    char buf[len];
    snprintf(buf, len, "[%s, %s]", vs_path, fs_path);
    _log_and_fail(self.handle, "linking", buf, glGetProgramInfoLog, glGetProgramiv);
  }

  glDetachShader(self.handle, vs_handle);
  glDetachShader(self.handle, fs_handle);
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

void shader_use(Shader self) {
  shader_bind(self);
}
