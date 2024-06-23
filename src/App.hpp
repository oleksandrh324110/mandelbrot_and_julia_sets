#pragma once

#include "gfx/gfx.hpp"

namespace app {
class App {
 public:
  App();
  ~App();

  void run();

  ImGuiIO& get_imgui_io() const;

 private:
  gfx::Window mandelbrot_window;
  gfx::Window julia_window;

  void init();
  void main_loop();
  void cleanup();
};
}  // namespace app