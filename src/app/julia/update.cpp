#include "include.hpp"

void julia_update_callback(App& app) {
  auto& window = app.julia;

  const float aspect = window.size.x / window.size.y;

  static glm::vec2 top_left = glm::vec2(-1, 1);
  static glm::vec2 bottom_right = glm::vec2(1, -1);
  static float hue_shift = 0.5;
  static bool hue_shift_animate = false;
  static float zoom = 1;
  static float smooth_zoom = 1;
  static int max_iterations = 128;

  if (window.mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down)
    window.central_point -= glm::vec2(window.mouse.delta.x * aspect, window.mouse.delta.y) * 2.f / window.size / zoom;

  if (window.mouse.zoom.y > 0)
    zoom *= 1.5;
  else if (window.mouse.zoom.y < 0)
    zoom /= 1.5;

  zoom = std::max(0.1f, zoom);
  max_iterations = std::max(1, max_iterations);
  smooth_zoom = glm::mix(smooth_zoom, zoom, window.delta_time * 10);

  if (hue_shift_animate) {
    hue_shift += window.delta_time / 5;
    if (hue_shift > 1)
      hue_shift = 0;
  }

  float width = (bottom_right.x - top_left.x) / smooth_zoom;
  float height = (top_left.y - bottom_right.y) / smooth_zoom;

  glm::vec2 new_top_left = window.central_point + glm::vec2(-width / 2 * aspect, height / 2);
  glm::vec2 new_bottom_right = window.central_point + glm::vec2(width / 2 * aspect, -height / 2);

  window.shader->use();
  window.shader->set_uniform("framebuffer_size", window.framebuffer_size);
  window.shader->set_uniform("top_left", new_top_left);
  window.shader->set_uniform("bottom_right", new_bottom_right);
  window.shader->set_uniform("hue_shift", hue_shift);
  window.shader->set_uniform("max_iterations", max_iterations);
  window.shader->set_uniform("pow", app.pow);
  window.shader->set_uniform("c", app.mandelbrot.central_point);

  ImGui::Begin("julia Set");
  ImGui::Text("FPS: %f", 1 / window.delta_time);
  ImGui::SliderInt("Max Iterations", &max_iterations, 1, 1024);
  ImGui::SliderFloat("Pow", &app.pow, 1, 10);
  ImGui::SliderFloat("Hue shift", &hue_shift, 0, 1);
  ImGui::Checkbox("Animate hue shift", &hue_shift_animate);
  ImGui::End();
}
