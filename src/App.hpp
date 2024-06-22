#pragma once

#include "gfx/gfx.hpp"
#include "gfx/shader.hpp"
#include "gfx/vao.hpp"
#include "gfx/vbo.hpp"
#include "gfx/window.hpp"
#include "util/util.hpp"

namespace app {
class App {
 public:
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