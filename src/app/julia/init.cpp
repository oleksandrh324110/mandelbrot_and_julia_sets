#include "include.hpp"

void julia_init_callback(App& app) {
  auto& window = app.julia;

  window.set_pos(1000, 350);

  float vertices[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  window.vao = new VAO();
  window.vbo = new VBO(GL_ARRAY_BUFFER, false);
  window.ebo = new VBO(GL_ELEMENT_ARRAY_BUFFER, false);

  window.vao->bind();
  window.vbo->bind();
  window.vbo->set_data(vertices, sizeof(vertices));

  window.ebo->bind();
  window.ebo->set_data(indices, sizeof(indices));

  window.vao->set_attrib(*window.vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

  window.shader = new Shader("../res/shaders/julia_set.vs", "../res/shaders/julia_set.fs");
}
