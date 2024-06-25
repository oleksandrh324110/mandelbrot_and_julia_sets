#include "window.hpp"

namespace gfx {
Window::Window(glm::vec2 size, const char* title) {
  glfw_init();
  handle = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!handle)
    throw std::runtime_error("Failed to create GLFW window");
  glfwMakeContextCurrent(handle);
  glfwSwapInterval(1);

  glad_init();

  glfwSetWindowUserPointer(handle, this);
  glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* window, int width, int height) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    self.make_current();
    glViewport(0, 0, width, height);
  });

  glfwSetCursorPosCallback(handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    self.mouse.delta = glm::vec2(x, y) - self.mouse.position;
    self.mouse.position = {x, y};
  });

  glfwSetScrollCallback(handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    if (self.keyboard.keys[GLFW_KEY_LEFT_SHIFT].down)
      self.mouse.scroll = {y, x};
    else
      self.mouse.scroll = {x, y};
  });

  glfwSetMouseButtonCallback(handle, [](GLFWwindow* window, int button, int action, int mods) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    Button& b = self.mouse.buttons[button];
    b.down = action != GLFW_RELEASE;
    b.pressed = b.down && !b.last;
    b.last = b.down;
  });

  glfwSetKeyCallback(handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    Button& b = self.keyboard.keys[key];
    b.down = action != GLFW_RELEASE;
    b.pressed = b.down && !b.last;
    b.last = b.down;

    if (self.keyboard.keys[GLFW_KEY_Q].pressed)
      self.set_should_close(true);
  });
}

Window::~Window() {
  delete vao;
  delete vbo;
  delete ebo;
  delete shader;

  glfwDestroyWindow(handle);
}

void Window::update() {
  make_current();
  poll_events();

  time = glfwGetTime();
  delta_time = time - last_time;
  last_time = time;

  mouse.smooth_position = glm::mix(mouse.smooth_position, mouse.position, 0.1);
  mouse.smooth_delta = glm::mix(mouse.smooth_delta, mouse.delta, 0.1);
  mouse.smooth_scroll = glm::mix(mouse.smooth_scroll, mouse.scroll, 0.1);

  update_callback();
}

void Window::render() const {
  make_current();
  render_callback();
}

void Window::make_current() const { glfwMakeContextCurrent(handle); }

void Window::clear(glm::vec4 color = {1, 1, 1, 1}) const {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(GL_COLOR_BUFFER_BIT);
}
void Window::swap() const { glfwSwapBuffers(handle); }
void Window::poll_events() const { glfwPollEvents(); }
void Window::wait_events() const { glfwWaitEvents(); }
bool Window::should_close() const { return glfwWindowShouldClose(handle); }
void Window::set_should_close(bool value) { glfwSetWindowShouldClose(handle, value); }
}  // namespace gfx