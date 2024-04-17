#include <stdio.h>
#include <stdlib.h>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "cglm/struct.h"

static void _cursor_enter_callback(GLFWwindow* window, int entered) {
  printf(entered ? "enter\n" : "leave\n");
}

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
  glfwSetCursorEnterCallback(window, _cursor_enter_callback);

  gladLoadGL(glfwGetProcAddress);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetInputMode(window, GLFW_CURSOR, glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
