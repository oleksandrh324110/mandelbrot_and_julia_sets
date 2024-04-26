#include "util/util.h"

#include "gfx/gfx.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/shader.h"

#include <math.h>

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
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

  const GLFWvidmode* vide_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  (void)vide_mode;

  struct Dir {
    int x;
    int y;
  };

  struct Dir dir = {1, 1};

  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 0);

    xPos += dir.x;
    yPos += dir.y;

    printf("%lf, %lf\n", xPos, yPos);

    if (xPos < 0 || xPos >= 720) {
      xPos = glm_clamp(xPos, 0, 720);
      dir.x *= -1;
    } else if (yPos < 0 || yPos >= 480) {
      yPos = glm_clamp(yPos, 0, 480);
      dir.y *= -1;
    }

    glfwSetCursorPos(window, xPos, yPos);

    shader_bind(shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
