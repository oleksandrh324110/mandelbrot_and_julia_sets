#include "window.hpp"

Window::Window() {}
Window::Window(glm::vec2 size, std::string title) : size(size), title(title) {
  handle = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
  if (!handle)
    throw std::runtime_error("Failed to create GLFW window");
  glfwMakeContextCurrent(handle);
  glfwSwapInterval(1);

  glfwSetWindowUserPointer(handle, this);
  glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);
  glfwSetWindowPosCallback(handle, pos_callback);
  glfwSetCursorPosCallback(handle, cursor_pos_callback);
  glfwSetScrollCallback(handle, scroll_callback);
  glfwSetMouseButtonCallback(handle, mouse_button_callback);
  glfwSetKeyCallback(handle, key_callback);
}

Window::~Window() {
  cleanup();
  glfwDestroyWindow(handle);
}

void Window::init() {
  make_current();

  if (!init_callback) {
    std::stringstream ss;
    ss << "No init callback set for " << title << '\n';
    std::runtime_error(ss.str());
  }

  init_callback();
}

void Window::update() {
  make_current();

  time = glfwGetTime();
  delta_time = time - last_time;
  last_time = time;

  mouse.smooth_pos = glm::mix(mouse.smooth_pos, mouse.pos, 0.1);
  mouse.smooth_delta = glm::mix(mouse.smooth_delta, mouse.delta, 0.1);
  mouse.smooth_scroll = glm::mix(mouse.smooth_scroll, mouse.scroll, 0.1);

  if (!update_callback) {
    std::stringstream ss;
    ss << "No update callback set for " << title << '\n';
    std::runtime_error(ss.str());
  }

  update_callback();
}

void Window::render() {
  make_current();

  if (!render_callback) {
    std::stringstream ss;
    ss << "No render callback set for " << title << '\n';
    std::runtime_error(ss.str());
  }

  render_callback();
  swap_buffers();
  glfwPollEvents();
}

void Window::cleanup() {
  make_current();

  if (!cleanup_callback) {
    std::stringstream ss;
    ss << "No cleanup callback set for " << title << '\n';
    std::runtime_error(ss.str());
  }

  cleanup_callback();
}

void Window::make_current() const { glfwMakeContextCurrent(handle); }

void Window::clear(glm::vec4 color) const {
  float _color = math::map(mouse.pos.x, 0, size.x, 0, 1);
  glClearColor(_color, _color, _color, _color);
  glClear(GL_COLOR_BUFFER_BIT);
}
void Window::swap_buffers() const { glfwSwapBuffers(handle); }
bool Window::should_close() const { return glfwWindowShouldClose(handle); }
void Window::focus() const {
  glfwFocusWindow(handle);
  glfwSetWindowAttrib(handle, GLFW_FOCUSED, true);
}
bool Window::is_on_focus() const { return glfwGetWindowAttrib(handle, GLFW_FOCUSED); }
void Window::set_should_close(bool value) { glfwSetWindowShouldClose(handle, value); }

void Window::set_pos(glm::vec2 pos) {
  glfwSetWindowPos(handle, pos.x, pos.y);
  this->pos = pos;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.make_current();
  self.size = {width, height};
  glViewport(0, 0, width, height);
}

void Window::pos_callback(GLFWwindow* window, int x, int y) {
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.pos = {x, y};
}

void Window::cursor_pos_callback(GLFWwindow* window, double x, double y) {
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.mouse.delta = glm::vec2(x, y) - self.mouse.pos;
  self.mouse.pos = {x, y};
}

void Window::scroll_callback(GLFWwindow* window, double x, double y) {
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  if (self.keyboard.keys[GLFW_KEY_LEFT_SHIFT].down)
    self.mouse.scroll = {y, x};
  else
    self.mouse.scroll = {x, y};
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  Button& b = self.mouse.buttons[button];
  b.down = action != GLFW_RELEASE;
  b.pressed = b.down && !b.last;
  b.last = b.down;
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  Button& b = self.keyboard.keys[key];
  b.down = action != GLFW_RELEASE;
  b.pressed = b.down && !b.last;
  b.last = b.down;

  if (self.keyboard.keys[GLFW_KEY_Q].down)
    self.set_should_close(true);
}
