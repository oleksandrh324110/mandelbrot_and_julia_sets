#include "window.hpp"

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

void imgui_init(GLFWwindow* window) {
  static bool imgui_initialized = false;
  if (imgui_initialized)
    return;
  imgui_initialized = true;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad |
      ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
  ImGui::StyleColorsLight();
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

namespace gfx {
Window::Window(glm::vec2 size, const char* title) {
  glfw_init();
  _handle = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!_handle)
    throw std::runtime_error("Failed to create GLFW window");
  glfwMakeContextCurrent(_handle);
  glad_init();
  imgui_init(_handle);

  glfwSetWindowUserPointer(_handle, this);
  glfwSetFramebufferSizeCallback(_handle,
                                 [](GLFWwindow* window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });

  glfwSetCursorPosCallback(_handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    self.mouse.position = {x, y};
  });

  glfwSetMouseButtonCallback(
      _handle, [](GLFWwindow* window, int button, int action, int mods) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);
        Button& b = self.mouse.buttons[button];
        b.down = action != GLFW_RELEASE;
        b.pressed = b.down && !b.last;
        b.last = b.down;
      });

  glfwSetScrollCallback(_handle, [](GLFWwindow* window, double x, double y) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    self.mouse.scroll = {x, y};
  });

  glfwSetKeyCallback(_handle, [](GLFWwindow* window, int key, int scancode,
                                 int action, int mods) {
    Window& self = *(Window*)glfwGetWindowUserPointer(window);
    Button& b = self.keyboard.keys[key];
    b.down = action != GLFW_RELEASE;
    b.pressed = b.down && !b.last;
    b.last = b.down;
  });
}

Window::~Window() { glfwDestroyWindow(_handle); }

void Window::update() {}

void Window::clear() const {
  glClearColor(0.2, 0.2, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}
ImGuiIO& Window::get_imgui_io() const { return ImGui::GetIO(); }
}  // namespace gfx