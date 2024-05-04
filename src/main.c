#include "util/util.h"

#include "gfx/gfx.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/shader.h"
#include "gfx/window.h"

Shader shader;

void init() {
  window.mouse.zoom = window.mouse.smooth_zoom = 1;
}

void destroy() {

}

void update() {
  if (window.keyboard.keys[GLFW_KEY_Q].pressed)
    glfwSetWindowShouldClose(window.handle, GLFW_TRUE);

  if (window.mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down) {
    glfwSetCursor(window.handle, window.mouse.hand_cursor);
    window.mouse.scroll.x += -window.mouse.delta.x / window.size.x * window.aspect_ratio;
    window.mouse.scroll.y += window.mouse.delta.y / window.size.y;
  } else {
    glfwSetCursor(window.handle, window.mouse.arrow_cursor);
  }

  window.mouse.smooth_scroll = glms_vec2_add(
    window.mouse.smooth_scroll,
    glms_vec2_scale(glms_vec2_sub(window.mouse.scroll, window.mouse.smooth_scroll), 0.1)
  );
  window.mouse.smooth_zoom += (window.mouse.zoom - window.mouse.smooth_zoom) * 0.1;

  shader_uniform_vec2(shader, "resolution", window.size);
  shader_uniform_vec2(shader, "scroll", window.mouse.smooth_scroll);
  shader_uniform_float(shader, "zoom", window.mouse.smooth_zoom);

  // printf("Resolution: %f, %f\n", window.size.x, window.size.y);
  // printf("Scroll: %f, %f\n", window.mouse.smooth_scroll.x, window.mouse.smooth_scroll.y);
  // printf("Zoom: %f\n", window.mouse.smooth_zoom);
}

void render() {
  glClearColor(1, 0, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(void) {
  window_create((vec2s) { { 1440, 820 } }, "Hello, World!", init, destroy, update, render);

  GLfloat vertices[] = {
    1, 1, 0,
    1, -1, 0,
    -1, -1, 0,
    -1, 1, 0
  };
  GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  VBO vbo = vbo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  VBO ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
  VAO vao = vao_create();

  vao_bind(vao);

  vbo_bind(vbo);
  vbo_buffer(vbo, sizeof(vertices), vertices);

  vbo_bind(ebo);
  vbo_buffer(ebo, sizeof(indices), indices);

  vao_attrib(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);

  VertexAttr attr[] = { { 0, "aPos" } };
  shader = shader_create("res/shaders/main.vs", "res/shaders/main.fs", 1, attr);
  shader_use(shader);

  window_loop();
  return 0;
}
