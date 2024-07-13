#include "glfw.hpp"

glfw::glfw() {
  glfwSetErrorCallback(
      [](int error, const char* description) { throw std::runtime_error(description); });

  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif
}

glfw::~glfw() { glfwTerminate(); }