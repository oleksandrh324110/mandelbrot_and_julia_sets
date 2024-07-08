#pragma once

#include "../gfx/gfx.hpp"
#include "../utils/utils.hpp"

class App {
 public:
  glfw _glfw;
  Window mandelbrot = Window({720, 480}, "Mandelbrot Set");
  Window julia = Window({720, 480}, "Julia Set");
  glad _glad;
  imgui _imgui = imgui(julia.handle);

  VAO vao;
  VBO vbo = VBO(GL_ARRAY_BUFFER, false);
  VBO ebo = VBO(GL_ELEMENT_ARRAY_BUFFER, false);

  App();
  ~App();

  void run();

 private:
  void init();
  void main_loop();
  void cleanup();
};
