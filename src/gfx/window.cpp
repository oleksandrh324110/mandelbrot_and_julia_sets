#include "window.hpp"

Window::Window(glm::vec2 size, std::string title, GLFWwindow* share) : size(size), title(title) {
  handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, share);
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
  init_callback();
}

void Window::update() {
  make_current();

  time = glfwGetTime();
  delta_time = time - last_time;

  mouse.delta = mouse.pos - mouse.last_pos;

  update_callback();

  mouse.last_pos = mouse.pos;
  last_time = time;
  mouse.zoom = glm::vec2(0);
}

void Window::render() {
  make_current();
  render_callback();
}

void Window::cleanup() {
  make_current();

  delete vao;
  delete vbo;
  delete ebo;
  delete shader;
  vao = nullptr;
  vbo = nullptr;
  ebo = nullptr;
  shader = nullptr;

  cleanup_callback();
}

void Window::make_current() const { glfwMakeContextCurrent(handle); }

void Window::clear() const {
  glClearColor(1, 0, 1, 1);
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

void Window::set_pos(int x, int y) {
  if (ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemHovered())
    return;
  glfwSetWindowPos(handle, x, y);
  this->pos = {x, y};
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  if (ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemHovered())
    return;
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.size = {width, height};
  self.make_current();
  glViewport(0, 0, width, height);
}

void Window::pos_callback(GLFWwindow* window, int x, int y) {
  if (ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemHovered())
    return;
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.pos = {x, y};
}

void Window::cursor_pos_callback(GLFWwindow* window, double x, double y) {
  if (ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemHovered())
    return;
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.mouse.pos = {x, y};
}

void Window::scroll_callback(GLFWwindow* window, double x, double y) {
  if (ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemHovered())
    return;
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  self.mouse.zoom += glm::vec2(x, y);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemHovered())
    return;
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  Button& b = self.mouse.buttons[button];
  b.down = action != GLFW_RELEASE;
  b.pressed = b.down && !b.last;
  b.last = b.down;
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (ImGui::IsAnyItemActive() || ImGui::IsAnyItemFocused() || ImGui::IsAnyItemHovered())
    return;
  Window& self = *(Window*)glfwGetWindowUserPointer(window);
  Button& b = self.keyboard.keys[key];
  b.down = action != GLFW_RELEASE;
  b.pressed = b.down && !b.last;
  b.last = b.down;
}
