#include "include.hpp"

void mandelbrot_update_callback(App& app) {
  auto& window = app.mandelbrot;

  ImGui::Begin("Mandelbrot Set");
  ImGui::ColorEdit4("Clear Color", &window.clear_color[0]);
  ImGui::End();
}
