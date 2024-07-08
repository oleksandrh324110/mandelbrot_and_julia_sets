#include "include.hpp"

void julia_update_callback(App& app) {
  auto& window = app.julia;

  ImGui::Begin("Julia Set");
  ImGui::SliderFloat("Color", &window.color, 0.0f, 1.0f);
  ImGui::End();
}
