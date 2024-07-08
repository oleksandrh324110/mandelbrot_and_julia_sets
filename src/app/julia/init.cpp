#include "../app.hpp"

void julia_init_callback(App& app) {
  auto& window = app.julia;

  window.set_pos({200, 300});

  float vertices[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glGenVertexArrays(1, &window.VAO);
  glGenBuffers(1, &window.VBO);
  glGenBuffers(1, &window.EBO);

  glBindVertexArray(window.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, window.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, window.EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  window.shader = Shader("../res/shaders/julia_set.vs", "../res/shaders/julia_set.fs");
}
