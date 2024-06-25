#pragma once

#include "utils.hpp"

namespace gfx {
void imgui_init(GLFWwindow* handle);
void imgui_new_frame();
void imgui_render();
void imgui_shutdown();
}