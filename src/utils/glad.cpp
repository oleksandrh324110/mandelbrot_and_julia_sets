#include "glad.hpp"

glad::glad() {
  if (!gladLoadGL(glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize GLAD");
}
