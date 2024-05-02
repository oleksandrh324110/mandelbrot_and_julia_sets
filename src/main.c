#include "util/util.h"

#include "gfx/gfx.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/shader.h"

vec2s rect_coords;
vec2s scroll_vel;

static void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

static void _scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  scroll_vel.x += xoffset;
  scroll_vel.y += -yoffset;
}

static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  static bool pressed = false;

  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    if (pressed) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      pressed = false;
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      pressed = true;
    }
  }

  if (key == GLFW_KEY_LEFT && action != GLFW_RELEASE) {
    rect_coords.x -= 1.0 / 100;
  } if (key == GLFW_KEY_RIGHT && action != GLFW_RELEASE) {
    rect_coords.x += 1.0 / 100;
  } if (key == GLFW_KEY_UP && action != GLFW_RELEASE) {
    rect_coords.y += 1.0 / 100;
  } if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE) {
    rect_coords.y -= 1.0 / 100;
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
  glfwSetKeyCallback(window, _key_callback);
  glfwSetScrollCallback(window, _scroll_callback);

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

  VertexAttr attributes[] = {{0, "aPos"}};
  Shader shader = shader_create("res/shaders/main.vs", "res/shaders/main.fs", 1, attributes);

  vbo_bind(ebo);
  while (!glfwWindowShouldClose(window)) {
    rect_coords.x += (scroll_vel.x - rect_coords.x) * 0.1;
    rect_coords.y += (scroll_vel.y - rect_coords.y) * 0.1;

    glClearColor(47 / 255.0, 43 / 255.0, 48 / 255.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_use(shader);
    shader_uniform_vec2(shader, "offset", rect_coords);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
