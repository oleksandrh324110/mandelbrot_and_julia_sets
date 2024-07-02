#include "window.hpp"

Window::Window() {}
Window::Window(glm::vec2 size, std::string title) {
  handle = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
  if (!handle)
    throw std::runtime_error("Failed to create GLFW window");
  glfwMakeContextCurrent(handle);
  glfwSwapInterval(1);

  glfwSetWindowUserPointer(handle, this);
  glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);
  glfwSetCursorPosCallback(handle, cursor_pos_callback);
  glfwSetScrollCallback(handle, scroll_callback);
  glfwSetMouseButtonCallback(handle, mouse_button_callback);
  glfwSetKeyCallback(handle, key_callback);
}

Window::~Window() { glfwDestroyWindow(handle); }

void Window::update() {
  make_current();

  time = glfwGetTime();
  delta_time = time - last_time;
  last_time = time;

  mouse.smooth_pos = glm::mix(mouse.smooth_pos, mouse.pos, 0.1);
  mouse.smooth_delta = glm::mix(mouse.smooth_delta, mouse.delta, 0.1);
  mouse.smooth_scroll = glm::mix(mouse.smooth_scroll, mouse.scroll, 0.1);
}

void Window::make_current() const { glfwMakeContextCurrent(handle); }

void Window::clear(glm::vec4 color = {1, 1, 1, 1}) const {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(GL_COLOR_BUFFER_BIT);
}
void Window::swap() const { glfwSwapBuffers(handle); }
bool Window::should_close() const { return glfwWindowShouldClose(handle); }
void Window::set_should_close(bool value) { glfwSetWindowShouldClose(handle, value); }

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.make_current();
  glViewport(0, 0, width, height);
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
