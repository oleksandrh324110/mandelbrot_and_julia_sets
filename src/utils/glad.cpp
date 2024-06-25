#include "glad.hpp"

namespace gfx {
void glad_init() {
  if (!gladLoadGL(glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize GLAD");
}
}  // namespace gfx