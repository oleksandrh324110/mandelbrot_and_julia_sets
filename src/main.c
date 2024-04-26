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
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(720, 480, "OpenGL", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(window, _framebuffer_size_callback);
  glfwSetKeyCallback(window, _key_callback);

  gladLoadGL(glfwGetProcAddress);

  static GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  VAO vao = vao_create();
  VBO vbo = vbo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

  vao_bind(vao);
  vbo_bind(vbo);

  vbo_buffer(vbo, sizeof(vertices), vertices);
  vao_attrib(0, 3, GL_FLOAT, 3 * sizeof(float), 0);

  Shader shader = shader_create("res/shaders/main.vs", "res/shaders/main.fs", 0, NULL);

  double last_second = glfwGetTime();
  double last_time = glfwGetTime();

  char* title = malloc(10);

  while (!glfwWindowShouldClose(window)) {
    double now = glfwGetTime();

    if (now - last_second >= 1) {
      snprintf(title, 10, "fps: %.0lf\n", 1 / (now - last_time));
      glfwSetWindowTitle(window, title);
      last_second = glfwGetTime();
    }

    last_time = glfwGetTime();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 0);

    shader_bind(shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
