#include <stdio.h>
#include <stdlib.h>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "cglm/struct.h"

int main(void) {
  glfwInit();

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(720, 480, "OpenGL", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  gladLoadGL(glfwGetProcAddress);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  ivec2s screen_size;
  ivec2s window_pos;
  ivec2s window_mouse_pos;
  ivec2s screen_mouse_pos;

  double x, y;
  int x_dir = 1, y_dir = 1;

  while (!glfwWindowShouldClose(window)) {
    glfwGetWindowPos(window, &window_pos.x, &window_pos.y);
    glfwGetCursorPos(window, &x, &y);
    window_mouse_pos.x = x;
    window_mouse_pos.y = y;
    screen_mouse_pos = glms_ivec2_add(window_mouse_pos, window_pos);
    printf("%d, %d\n", screen_mouse_pos.x, screen_mouse_pos.y);

    if (screen_mouse_pos.x <= 0 || screen_mouse_pos.x >= 1439)
      x_dir *= -1;
    if (screen_mouse_pos.y <= 0 || screen_mouse_pos.y >= 899)
      y_dir *= -1;

    x += x_dir * 2;
    y += y_dir * 2;

    glfwSetCursorPos(window, x, y);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
