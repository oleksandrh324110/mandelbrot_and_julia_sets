#include "App.hpp"

namespace app {
App::App() {
  gfx::glfw_init();
  gfx::glad_init();

  mandelbrot_window = gfx::Window({800, 800}, "Mandelbrot Set");
  julia_window = gfx::Window({800, 800}, "Julia Set");

  gfx::imgui_init();
  mandelbrot_window.imgui_init();
  julia_window.imgui_init();
}

App::~App() { cleanup(); }

void App::run() {
  init();
  main_loop();
  cleanup();
}

void App::init() {}

void App::cleanup() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
}
}  // namespace app