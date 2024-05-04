#include "window.h"

Window window;

static void _size_callback(GLFWwindow* handle, int width, int height) {
  glViewport(0, 0, width, height);
  window.size = (vec2s){ { width, height } };
  window.aspect_ratio = (float)width / (float)height;
}

static void _cursor_callback(GLFWwindow* handle, double x, double y) {
  window.mouse.delta = glms_vec2_sub((vec2s) { { x, y } }, window.mouse.pos);
  window.mouse.pos = (vec2s){ { x, y } };
}

static void _key_callback(GLFWwindow* handle, int key, int scancode, int action, int mods) {
  Button* button = &window.keyboard.keys[key];
  button->down = action == GLFW_PRESS;
  button->pressed = button->down && !button->last;
  button->last = button->down;
}

static void _mouse_callback(GLFWwindow* handle, int button, int action, int mods) {
  Button* b = &window.mouse.buttons[button];
  b->down = action == GLFW_PRESS;
  b->pressed = b->down && !b->last;
  b->last = b->down;
}

static void _scroll_callback(GLFWwindow* handle, double x, double y) {

#ifdef __APPLE__
  if (window.keyboard.keys[GLFW_KEY_LEFT_CONTROL].down)
    window.mouse.zoom = y;
  else
    window.mouse.scroll = (vec2s){ { x, y } };
#endif

  if (window.keyboard.keys[GLFW_KEY_LEFT_CONTROL].down)
    window.mouse.zoom += y;
  else
    window.mouse.scroll = glms_vec2_add(
      window.mouse.scroll,
      window.keyboard.keys[GLFW_KEY_LEFT_SHIFT].down ? (vec2s) { { -y, 0 } } : (vec2s) { { 0, y } }
  );

  window.mouse.zoom = fmax(1, window.mouse.zoom);
}

static void _error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

void window_create(vec2s size, const char* title, FWindow init, FWindow destroy, FWindow update, FWindow render) {
  window.size = size;
  window.init = init;
  window.destroy = destroy;
  window.update = update;
  window.render = render;

  if (!glfwInit()) {
    fprintf(stderr, "Error initializing GLFW\n");
    exit(1);
  }

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

  window.handle = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
  if (!window.handle) {
    fprintf(stderr, "Error creating window\n");
    exit(1);
  }

  glfwMakeContextCurrent(window.handle);
  gladLoadGL(glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window.handle, _size_callback);
  glfwSetCursorPosCallback(window.handle, _cursor_callback);
  glfwSetKeyCallback(window.handle, _key_callback);
  glfwSetMouseButtonCallback(window.handle, _mouse_callback);
  glfwSetScrollCallback(window.handle, _scroll_callback);
  glfwSetErrorCallback(_error_callback);

  glfwSwapInterval(1);
}

void window_loop(void) {
  window.mouse.arrow_cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  window.mouse.hand_cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
  window.aspect_ratio = (float)window.size.x / (float)window.size.y;

  window.init();

  double last = glfwGetTime();
  while (!glfwWindowShouldClose(window.handle)) {
    double now = glfwGetTime();
    window.time = now;
    window.delta_time = now - last;
    last = now;

    window.update();
    window.render();

    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }

  window.destroy();
  glfwDestroyWindow(window.handle);
  glfwTerminate();
}