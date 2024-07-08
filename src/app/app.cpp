#include "app.hpp"

#include "julia/cleanup.cpp"
#include "julia/init.cpp"
#include "julia/render.cpp"
#include "julia/update.cpp"
#include "mandelbrot/cleanup.cpp"
#include "mandelbrot/init.cpp"
#include "mandelbrot/render.cpp"
#include "mandelbrot/update.cpp"

App::App() { init(); }
void App::run() { main_loop(); }
void App::init() {
  float vertices[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  vao.bind();
  vbo.bind();
  vbo.set_data(vertices, sizeof(vertices));

  ebo.bind();
  ebo.set_data(indices, sizeof(indices));

  vao.set_attrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

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
    _imgui.new_frame();

    mandelbrot.update();
    julia.update();

    mandelbrot.render();
    julia.render();

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