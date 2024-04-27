#include "util/util.h"

#include "gfx/gfx.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/shader.h"

void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  static bool pressed = false;

  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    if (pressed) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      pressed = false;
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      pressed = true;
    }
  }
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

  GLfloat vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f   // top left 
  };

  GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  VBO vbo = vbo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  VBO ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
  VAO vao = vao_create();

  vbo_bind(vbo);
  vbo_buffer(vbo, sizeof(vertices), vertices);

  vbo_bind(ebo);
  vbo_buffer(ebo, sizeof(indices), indices);

  vao_bind(vao);
  vao_attrib(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

  Shader shader = shader_create("res/shaders/main.vs", "res/shaders/main.fs", 0, NULL);

  vbo_bind(ebo);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(239 / 255.0, 234 / 255.0, 234 / 255.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_use(shader);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
