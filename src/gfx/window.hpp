#pragma once

#include "../utils/utils.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "vbo.hpp"

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
  GLFWwindow* handle;
  glm::vec2 size;
  const char* title;

  Mouse mouse;
  Keyboard keyboard;

  VAO* vao;
  VBO* vbo;
  VBO* ebo;
  Shader* shader;

  double time;
  double last_time;
  double delta_time;

  Window(glm::vec2 size, const char* title);
  ~Window();

  std::function<void()> update_callback;
  std::function<void()> render_callback;

  void update();
  void render() const;

  void make_current() const;

  void clear(glm::vec4 color) const;
  void swap() const;

  void poll_events() const;
  void wait_events() const;

  bool should_close() const;
  void set_should_close(bool value);
};
}  // namespace gfx