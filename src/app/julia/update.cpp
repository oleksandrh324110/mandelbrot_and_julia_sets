#include "include.hpp"

void julia_update_callback(App& app) {
  auto& window = app.julia;

  ImGui::Begin("Julia Set");
  ImGui::ColorEdit4("Clear Color", &window.clear_color[0]);
  ImGui::End();
}
