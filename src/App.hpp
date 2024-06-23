#pragma once

#include "gfx/gfx.hpp"
#include "util/util.hpp"

namespace app {
class App {
 public:
  ImGuiIO& imgui_io;

  App();
  ~App();

  void run();

 private:
  gfx::Window mandelbrot_window;
  gfx::Window julia_window;

  void init();
  void main_loop();
  void cleanup();
};
}  // namespace app