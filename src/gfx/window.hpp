#pragma once

#include "../utils/utils.hpp"
#include "shader.hpp"

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
  glm::ivec2 pos;
  std::string title;

  Mouse mouse;
  Keyboard keyboard;

  double time;
  double last_time;
  double delta_time;

  Window();
  Window(glm::vec2 size, std::string title);
  ~Window();

  GLuint VAO, VBO, EBO;
  Shader shader;

  std::function<void()> init_callback;
  std::function<void()> update_callback;
  std::function<void()> render_callback;
  std::function<void()> cleanup_callback;

  void init();
  void update();
  void render();
  void cleanup();

  void make_current() const;

  void clear(glm::vec4 color = {1, 1, 1, 1}) const;
  void swap_buffers() const;

  void focus() const;
  bool is_on_focus() const;
  bool should_close() const;
  void set_should_close(bool value);
  void set_pos(glm::vec2 pos);

 private:
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  static void pos_callback(GLFWwindow* window, int x, int y);
  static void cursor_pos_callback(GLFWwindow* window, double x, double y);
  static void scroll_callback(GLFWwindow* window, double x, double y);
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
