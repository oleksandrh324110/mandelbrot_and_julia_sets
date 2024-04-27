#include "util/util.h"

#include "gfx/gfx.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/shader.h"

void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void) {
  glfwInit();

  // glfwWindowHint(GLFW_SAMPLES, 2);
  // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
  // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(720, 480, "OpenGL", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(window, _framebuffer_size_callback);
  glfwSetKeyCallback(window, _key_callback);

  gladLoadGL(glfwGetProcAddress);

  static GLfloat vertices[] = {
    // coords       colors
   -0.5, -0.5, 0.0, 1, 0, 0,
    0.5, -0.5, 0.0, 0, 1, 0,
    0.0,  0.5, 0.0, 0, 0, 1,
  };

  VAO vao = vao_create();
  VBO vbo = vbo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

  vbo_bind(vbo);
  vao_bind(vao);

  vbo_buffer(vbo, sizeof(vertices), vertices);
  vao_attrib(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  vao_attrib(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));

  Shader shader = shader_create("res/shaders/main.vs", "res/shaders/main.fs", 0, NULL);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    shader_bind(shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
