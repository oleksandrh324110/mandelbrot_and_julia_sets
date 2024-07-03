#include "app.hpp"

App::App() { init(); }
void App::run() { main_loop(); }
void App::init() {
  mandelbrot.init_callback = [this]() {
    mandelbrot.set_pos({200, 300});

    float vertices[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
    float indices[] = {0, 1, 3, 1, 2, 3};

    glGenVertexArrays(1, &mandelbrot.VAO);
    glGenBuffers(1, &mandelbrot.VBO);
    glGenBuffers(1, &mandelbrot.EBO);

    glBindVertexArray(mandelbrot.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mandelbrot.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mandelbrot.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    mandelbrot.shader =
        Shader("../res/shaders/mandelbrot_set.vs", "../res/shaders/mandelbrot_set.fs");
  };
  mandelbrot.update_callback = [this]() {};
  mandelbrot.render_callback = [this]() {};
  mandelbrot.cleanup_callback = [this]() {};

  julia.init_callback = [this]() {
    julia.set_pos({1000, 300});
    float vertices[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
    float indices[] = {0, 1, 3, 1, 2, 3};

    glGenVertexArrays(1, &julia.VAO);
    glGenBuffers(1, &julia.VBO);
    glGenBuffers(1, &julia.EBO);

    glBindVertexArray(julia.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, julia.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, julia.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    julia.shader = Shader("../res/shaders/julia_set.vs", "../res/shaders/julia_set.fs");
  };
  julia.update_callback = [this]() {};
  julia.render_callback = [this]() {};
  julia.cleanup_callback = [this]() {};

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
  }
}
void App::cleanup() {}
App::~App() { cleanup(); }