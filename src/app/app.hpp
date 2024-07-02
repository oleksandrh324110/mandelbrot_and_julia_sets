#pragma once

#include "../gfx/gfx.hpp"
#include "../utils/utils.hpp"

class App {
 public:
  Window mandelbrot_set;
  Window julia_set;

  App();
  ~App();

  void run();

 private:
  void init();
  void main_loop();
  void cleanup();

  glad _glad;
  glfw _glfw;
  imgui _imgui;
};
