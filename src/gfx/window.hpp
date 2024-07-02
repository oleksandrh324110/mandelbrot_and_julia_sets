#pragma once

#include "../utils/utils.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "vbo.hpp"

struct Button {
  bool down : 1 = false;
  bool last : 1 = false;
  bool pressed : 1 = false;
};

struct Keyboard {
  Button keys[GLFW_KEY_LAST];
};

struct Mouse {
  Button buttons[GLFW_MOUSE_BUTTON_LAST];

  glm::vec2 pos;
  glm::vec2 delta;
  glm::vec2 scroll;
  glm::vec2 zoom;

  glm::vec2 smooth_pos;
  glm::vec2 smooth_delta;
  glm::vec2 smooth_scroll;
  glm::vec2 smooth_zoom;
};

class Window {
 public:
  GLFWwindow* handle;
  glm::vec2 size;
  glm::vec2 pos;
  std::string title;

  Mouse mouse;
  Keyboard keyboard;

  double time;
  double last_time;
  double delta_time;

  Window();
  Window(glm::vec2 size, std::string title);
  ~Window();

  void update();

  void make_current() const;

  void clear(glm::vec4 color) const;
  void swap() const;

  bool should_close() const;
  void set_should_close(bool value);

 private:
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  static void cursor_pos_callback(GLFWwindow* window, double x, double y);
  static void scroll_callback(GLFWwindow* window, double x, double y);
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
