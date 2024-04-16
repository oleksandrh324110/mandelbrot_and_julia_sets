#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct {
  bool down, last, pressed;
} Button;

typedef struct {
  Button buttons[GLFW_MOUSE_BUTTON_LAST];
  vec2s position, delta;
} Mouse;

typedef struct {
  Button buttons[GLFW_KEY_LAST];
} Keyboard;

typedef void (*FWindow)(void);

typedef struct {
  GLFWwindow* handle;
  ivec2s size;
  FWindow init, destroy, tick, update, render;
  Mouse mouse;
  Keyboard keyboard;

  double last_second;
  double last_frame, frame_delta;
  size_t frames, fps;
} Window;

extern Window window;

void window_create(int width, int height, const char* title, FWindow init, FWindow destroy, FWindow update, FWindow render);
void window_loop(void);
