#include "App.hpp"

App::App() {
  mandelbrot_window = new gfx::Window({720, 480}, "Mandelbrot Set");
  julia_window = new gfx::Window({720, 480}, "Julia Set");
}

App::~App() { cleanup(); }

void App::run() {
  init();
  main_loop();
}

void App::init() {
  gfx::imgui_init(julia_window->handle);

  GLfloat vertices[] = {-1, -1, 0, -1, 1, 0, 1, 1, 0, 1, -1, 0};
  GLuint indices[] = {0, 1, 2, 2, 3, 0};

  {
    gfx::Window& window = *(mandelbrot_window);
    window.vao = new gfx::VAO();
    window.vbo = new gfx::VBO(GL_ARRAY_BUFFER, false);
    window.vbo->buffer(vertices, 0, sizeof(vertices));
    window.ebo = new gfx::VBO(GL_ELEMENT_ARRAY_BUFFER, false);
    window.ebo->buffer(indices, 0, sizeof(indices));
    window.vao->attr(*window.vbo, 0, sizeof(vertices), GL_FLOAT, 3 * sizeof(float), 0);
    window.shader =
        new gfx::Shader("../res/shaders/mandelbrot_set.vs", "../res/shaders/mandelbrot_set.fs");
  }
  {
    gfx::Window& window = *(julia_window);
    window.vao = new gfx::VAO();
    window.vbo = new gfx::VBO(GL_ARRAY_BUFFER, false);
    window.vbo->buffer(vertices, 0, sizeof(vertices));
    window.ebo = new gfx::VBO(GL_ELEMENT_ARRAY_BUFFER, false);
    window.ebo->buffer(indices, 0, sizeof(indices));
    window.vao->attr(*window.vbo, 0, sizeof(vertices), GL_FLOAT, 3 * sizeof(float), 0);
    window.shader = new gfx::Shader("../res/shaders/julia_set.vs", "../res/shaders/julia_set.fs");
  }

  mandelbrot_window->update_callback = [&]() {
    static int polygon_mode = GL_FILL;

    ImGui::Begin("Mandelbrot Set");
    ImGui::Text("Polygon Mode");
    ImGui::RadioButton("Fill", &polygon_mode, GL_FILL);
    ImGui::RadioButton("Line", &polygon_mode, GL_LINE);
    ImGui::End();

    glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);

    mandelbrot_window->shader->use();
  };
  julia_window->update_callback = [&]() {
    static int polygon_mode = GL_FILL;

    ImGui::Begin("Julia Set");
    ImGui::Text("Polygon Mode");
    ImGui::RadioButton("Fill", &polygon_mode, GL_FILL);
    ImGui::RadioButton("Line", &polygon_mode, GL_LINE);
    ImGui::End();

    glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);

    julia_window->shader->use();
  };
  mandelbrot_window->render_callback = [&]() {
    mandelbrot_window->clear({0.5f, 0.1f, 0.1f, 1.0f});
    mandelbrot_window->shader->use();
    glBindVertexArray(mandelbrot_window->vao->handle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  };
  julia_window->render_callback = [&]() {
    julia_window->clear({0.5f, 0.1f, 0.1f, 1.0f});
    julia_window->shader->use();
    glBindVertexArray(julia_window->vao->handle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  };
}

void App::main_loop() {
  while (!mandelbrot_window->should_close() && !julia_window->should_close()) {
    gfx::imgui_new_frame();

    mandelbrot_window->update();
    mandelbrot_window->render();

    julia_window->update();
    julia_window->render();

    gfx::imgui_render();
    mandelbrot_window->swap();
    julia_window->swap();
  }
}

void App::cleanup() {
  gfx::imgui_shutdown();
  delete mandelbrot_window;
  delete julia_window;
  glfwTerminate();
}