#include "app.hpp"

#include "julia/include.hpp"
#include "mandelbrot/include.hpp"

App::App() { init(); }
void App::run() { main_loop(); }
void App::init() {
  mandelbrot.init_callback = [this]() { mandelbrot_init_callback(*this); };
  mandelbrot.update_callback = [this]() { mandelbrot_update_callback(*this); };
  mandelbrot.render_callback = [this]() { mandelbrot_render_callback(*this); };
  mandelbrot.cleanup_callback = [this]() { mandelbrot_cleanup_callback(*this); };

  julia.init_callback = [this]() { julia_init_callback(*this); };
  julia.update_callback = [this]() { julia_update_callback(*this); };
  julia.render_callback = [this]() { julia_render_callback(*this); };
  julia.cleanup_callback = [this]() { julia_cleanup_callback(*this); };

  mandelbrot.init();
  julia.init();
}
void App::main_loop() {
  while (!mandelbrot.should_close() && !julia.should_close()) {
    if (mandelbrot.keyboard.keys[GLFW_KEY_Q].down || julia.keyboard.keys[GLFW_KEY_Q].down)
      mandelbrot.set_should_close(true);

    _imgui.new_frame();

    mandelbrot.update();
    julia.update();

    mandelbrot.render();
    julia.render();

    mandelbrot.make_current();
    _imgui.render();

    glfwSwapBuffers(mandelbrot.handle);
    glfwSwapBuffers(julia.handle);
    glfwPollEvents();
  }
}
void App::cleanup() {
  mandelbrot.cleanup();
  julia.cleanup();
}
App::~App() { cleanup(); }