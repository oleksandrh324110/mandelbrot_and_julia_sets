#pragma once

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include "utils.hpp"

class imgui {
 public:
  imgui();
  imgui(GLFWwindow* handle);
  ~imgui();

  void new_frame();
  void render();
};