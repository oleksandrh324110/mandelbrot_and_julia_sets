#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct {
  bool down, last, pressed;
} Button;

typedef struct {
  Button buttons[GLFW_MOUSE_BUTTON_LAST];
  ivec2s position, delta;
} Mouse;

typedef struct {
  Button buttons[GLFW_KEY_LAST];
} Keyboard;

typedef void (*FWindow)();

typedef struct {
  GLFWwindow* handle;
  ivec2s size;
  FWindow init, destroy, tick, update, render;
  Mouse mouse;
  Keyboard keyboard;

  size_t last_second;
  size_t frames, fps, last_frame, frame_delta;
  size_t ticks, tps, tick_remainder;
} Window;

extern Window window;

void window_loop();
void window_create(int width, int height, const char* title, FWindow init, FWindow destroy, FWindow tick, FWindow update, FWindow render);
