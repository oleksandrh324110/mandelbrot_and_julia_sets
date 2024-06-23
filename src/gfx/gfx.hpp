#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "shader.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "window.hpp"

namespace gfx {}