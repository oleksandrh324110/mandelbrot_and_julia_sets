#pragma once

#include "../gfx/gfx.hpp"
#include "../utils/utils.hpp"

class App {
 public:
  glfw _glfw;
  Window mandelbrot = Window({720, 480}, "Mandelbrot Set");
  Window julia = Window({720, 480}, "Julia Set");
  glad _glad;
  imgui _imgui = imgui(mandelbrot.handle);

  App();
  ~App();

  void run();

 private:
  void init();
  void main_loop();
  void cleanup();
};
