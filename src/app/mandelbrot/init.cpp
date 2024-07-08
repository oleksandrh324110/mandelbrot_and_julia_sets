#include "../app.hpp"

void mandelbrot_init_callback(App& app) {
  auto& window = app.mandelbrot;

  window.set_pos({200, 300});

  window.shader = Shader("../res/shaders/mandelbrot_set.vs", "../res/shaders/mandelbrot_set.fs");
}
