#include "../app.hpp"

void julia_render_callback(App& app) {
  auto& window = app.julia;

  window.clear();
  window.shader.use();

  glBindVertexArray(window.VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
