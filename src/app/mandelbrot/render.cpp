#include "include.hpp"

void mandelbrot_render_callback(App &app) {
  auto &window = app.mandelbrot;

  window.clear();

  window.vao->bind();
  window.shader->use();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
