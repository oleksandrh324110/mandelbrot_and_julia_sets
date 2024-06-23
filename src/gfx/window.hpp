#pragma once

#include "includes.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "vbo.hpp"

namespace gfx {
void glfw_init();
void glad_init();
void imgui_init();
void imgui_new_frame();
void imgui_render();
void imgui_end_frame(ImGuiIO& io);

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

  std::function<void()> init_callback;
  std::function<void()> update_callback;
  std::function<void()> render_callback;
  std::function<void()> terminate_callback;

  void update();
  void render() const;

  void clear(glm::vec4 color) const;
  void swap() const;

  void poll_events() const;
  void wait_events() const;

  bool should_close() const;
  void set_should_close(bool value);

  void imgui_init() const;

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