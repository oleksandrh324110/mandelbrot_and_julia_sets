#include "window.hpp"

namespace gfx {
void glfw_init() {
  static bool glfw_initialized = false;
  if (glfw_initialized)
    return;
  glfw_initialized = true;

  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void glad_init() {
  static bool glad_initialized = false;
  if (glad_initialized)
    return;
  glad_initialized = true;

  if (!gladLoadGL(glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize GLAD");
}

void imgui_init() {
  static bool imgui_initialized = false;
  if (imgui_initialized)
    return;
  imgui_initialized = true;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad |
                    ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
  ImGui::StyleColorsLight();
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
}

void imgui_new_frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void imgui_render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_end_frame(ImGuiIO& io) {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  ImGui::EndFrame();

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

Window::Window() {}

Window::Window(glm::vec2 size, const char* title) {
  handle = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!handle)
    throw std::runtime_error("Failed to create GLFW window");
  glfwMakeContextCurrent(handle);

  glfwSetWindowUserPointer(handle, this);
  glfwSetFramebufferSizeCallback(
      handle, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });

  glfwSetCursorPosCallback(handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    self.mouse.position = {x, y};
  });

  glfwSetScrollCallback(handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
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

    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
      self.set_should_close(true);
  });
}

Window::~Window() { glfwDestroyWindow(handle); }

void Window::clear(glm::vec4 color = {1, 1, 1, 1}) const {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(GL_COLOR_BUFFER_BIT);
}
void Window::swap() const { glfwSwapBuffers(handle); }
void Window::poll_events() const { glfwPollEvents(); }
void Window::wait_events() const { glfwWaitEvents(); }
bool Window::should_close() const { return glfwWindowShouldClose(handle); }
void Window::set_should_close(bool value) { glfwSetWindowShouldClose(handle, value); }
void Window::imgui_init() const {
  ImGui_ImplGlfw_InitForOpenGL(handle, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}
}  // namespace gfx