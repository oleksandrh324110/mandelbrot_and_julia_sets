#pragma once

#include "includes.hpp"
#include "shader.cpp"
#include "vao.cpp"
#include "vbo.cpp"

namespace gfx {
struct Button {
  bool down, last, pressed;
};

struct Keyboard {
  Button keys[GLFW_KEY_LAST];
};

struct Mouse {
  Button buttons[GLFW_MOUSE_BUTTON_LAST];

  glm::vec2 position;
  glm::vec2 delta;
  glm::vec2 scroll;

  glm::vec2 smooth_position;
  glm::vec2 smooth_delta;
  glm::vec2 smooth_scroll;
};

class Window {
 public:
  glm::vec2 size;
  const char* title;

  Window();
  Window(glm::vec2 size, const char* title);
  ~Window();

  void init(std::function<void()> init_callback);
  void update(std::function<void()> update_callback);
  void render(std::function<void()> render_callback) const;
  void terminate(std::function<void()> terminate_callback);

  void clear(glm::vec4 color) const;
  void swap() const;

  void poll_events() const;
  void wait_events() const;

  bool should_close() const;
  void set_should_close(bool value);

 private:
  GLFWwindow* handle;

  Mouse mouse;
  Keyboard keyboard;

  GLfloat* vertices;
  GLuint* indicies;
  VAO vao;
  VBO vbo;
  VBO ebo;
  Shader shader;

  double time;
  double last_time;
  double delta_time;
};
}  // namespace gfx