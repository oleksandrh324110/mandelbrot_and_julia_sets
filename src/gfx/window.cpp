#include "window.hpp"

static bool glfw_initialized = false;
void glfw_init() {
  if (glfw_initialized)
    return;

  glfw_initialized = true;

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

static bool glad_initialized = false;
void glad_init() {
  if (glad_initialized)
    return;

  glad_initialized = true;

  gladLoadGL(glfwGetProcAddress);
}

static bool imgui_initialized = false;
void imgui_init(GLFWwindow* window) {
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
}

namespace app {
Window::Window(glm::vec2 size, const char* title) {}

void Window::clear() const {
  glClearColor(0.2, 0.2, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}
}  // namespace app