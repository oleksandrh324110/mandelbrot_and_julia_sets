#include "App.hpp"

static void glfw_init() {
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

static void glad_init() {
  static bool glad_initialized = false;
  if (glad_initialized)
    return;
  glad_initialized = true;

  if (!gladLoadGL(glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize GLAD");
}

static void imgui_init(GLFWwindow* window) {
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
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

static void imgui_new_frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}