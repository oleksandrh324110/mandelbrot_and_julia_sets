#pragma once

#include "gfx/gfx.hpp"
#include "utils/utils.hpp"

class App {
 public:
  App();
  ~App();

  void run();

 private:
  gfx::Window* mandelbrot_window;
  gfx::Window* julia_window;

  void init();
  void main_loop();
  void cleanup();
};
