#include "window.hpp"

namespace gfx {
Window::Window(glm::vec2 size, const char* title) {
  _handle = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!_handle)
    throw std::runtime_error("Failed to create GLFW window");
  glfwMakeContextCurrent(_handle);

  glfwSetWindowUserPointer(_handle, this);
  glfwSetFramebufferSizeCallback(
      _handle, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });

  glfwSetCursorPosCallback(_handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    self.mouse.position = {x, y};
  });

  glfwSetScrollCallback(_handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    self.mouse.scroll = {x, y};
  });

  glfwSetMouseButtonCallback(_handle, [](GLFWwindow* window, int button, int action, int mods) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    Button& b = self.mouse.buttons[button];
    b.down = action != GLFW_RELEASE;
    b.pressed = b.down && !b.last;
    b.last = b.down;
  });

  glfwSetKeyCallback(_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    Button& b = self.keyboard.keys[key];
    b.down = action != GLFW_RELEASE;
    b.pressed = b.down && !b.last;
    b.last = b.down;

    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
      self.set_should_close(true);
  });
}

Window::~Window() { glfwDestroyWindow(_handle); }

void Window::init(std::function<void()> init_callback) { init_callback(); }
void Window::update(std::function<void()> update_callback) { update_callback(); }
void Window::render(std::function<void()> render_callback) const { render_callback(); }
void Window::terminate(std::function<void()> terminate_callback) { terminate_callback(); }

void Window::clear(glm::vec4 color = {1, 1, 1, 1}) const {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(GL_COLOR_BUFFER_BIT);
}
void Window::swap() const { glfwSwapBuffers(_handle); }
void Window::poll_events() const { glfwPollEvents(); }
void Window::wait_events() const { glfwWaitEvents(); }
bool Window::should_close() const { return glfwWindowShouldClose(_handle); }
void Window::set_should_close(bool value) { glfwSetWindowShouldClose(_handle, value); }
}  // namespace gfx