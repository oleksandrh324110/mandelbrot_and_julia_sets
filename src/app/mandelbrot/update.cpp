#include "include.hpp"

void mandelbrot_update_callback(App& app) {
  auto& window = app.mandelbrot;

  const float aspect = window.size.x / window.size.y;

  static glm::vec2 top_left = glm::vec2(-2, 2);
  static glm::vec2 bottom_right = glm::vec2(2, -2);
  static float hue_shift = 0.5;
  static float zoom = 1;
  static float smooth_zoom = 1;
  static int max_iterations = 128;
  static int smooth_max_iterations = 128;

  if (window.mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down)
    window.central_point +=
        -glm::vec2(window.mouse.delta.x * 2, window.mouse.delta.y * 2) / zoom / window.size;

  if (window.mouse.zoom.y == 1)
    zoom *= 1.5;
  else if (window.mouse.zoom.y == -1)
    zoom /= 1.5;

  zoom = std::max(0.5f, zoom);
  smooth_zoom = glm::mix(smooth_zoom, zoom, 0.1);
  smooth_max_iterations = glm::mix(smooth_max_iterations, max_iterations, 0.1);

  max_iterations = std::max(1, max_iterations);
  smooth_max_iterations = std::max(1, smooth_max_iterations);

  float width = (bottom_right.x - top_left.x) / smooth_zoom;
  float height = (top_left.y - bottom_right.y) / smooth_zoom;

  glm::vec2 new_top_left = window.central_point + glm::vec2(-width / 2, height / 2);
  glm::vec2 new_bottom_right = window.central_point + glm::vec2(width / 2, -height / 2);

  window.shader->use();
  window.shader->set_uniform("resolution", window.size);
  window.shader->set_uniform(
      "top_left", glm::vec2(new_top_left.x * aspect, new_top_left.y) + window.central_point);
  window.shader->set_uniform(
      "bottom_right",
      glm::vec2(new_bottom_right.x * aspect, new_bottom_right.y) + window.central_point);
  window.shader->set_uniform("hue_shift", hue_shift);
  window.shader->set_uniform("max_iterations", max_iterations);

  ImGui::Begin("Mandelbrot Set");
  ImGui::Text("FPS: %.f", ImGui::GetIO().Framerate);
  ImGui::Text("Central point: (%f, %f)", window.central_point.x, window.central_point.y);
  ImGui::InputInt("Max Iterations", &max_iterations, 1, 10);
  ImGui::SliderFloat("Hue shift", &hue_shift, 0, 1);
  if (ImGui::Button("Exit"))
    window.set_should_close(true);
  ImGui::End();
}
