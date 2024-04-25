#include "gfx/gfx.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main(void) {
  glfwInit();

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(720, 480, "OpenGL", NULL, NULL);
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSwapInterval(1);

  static GLfloat vertices[] = {
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
  };

  VBO vbo = vbo_create(GL_ARRAY_BUFFER, false);
  vbo_bind(vbo);
  vbo_data(vbo, sizeof(vertices), vertices);

  VAO vao = vao_create();
  vao_bind(vao);
  vao_attrib(vao, vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

  Shader shader = shader_create("res/shaders/main.vs", "res/shaders/main.fs", 0, NULL);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0, 0.5, 0, 0);

    shader_use(shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}


