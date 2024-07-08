#include "include.hpp"

void mandelbrot_update_callback(App& app) {
  auto& window = app.mandelbrot;

  ImGui::Begin("Mandelbrot Set");
  ImGui::SliderFloat("Color", &window.color, 0.0f, 1.0f);
  ImGui::End();
}
