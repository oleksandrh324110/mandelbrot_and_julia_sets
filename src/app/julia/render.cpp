#include "include.hpp"

void julia_render_callback(App& app) {
  auto& window = app.julia;

  window.clear(window.clear_color);

  // window.vao->bind();
  // window.shader->use();
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
