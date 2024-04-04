#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct {
  bool down, last, last_tick, pressed, pressed_tick;
} Button;

typedef struct {
  Button buttons[GLFW_MOUSE_BUTTON_LAST];
  vec2s position, delta;
} Mouse;

typedef struct {
  Button keys[GLFW_KEY_LAST];
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
  size_t ticks, tps, tick_remainde;
} Window;

extern Window window;

void window_create(FWindow init, FWindow destroy, FWindow tick, FWindow update, FWindow render);
void window_loop();
void mouse_set_grabbed(bool grabbed);
bool mouse_get_grabbed();