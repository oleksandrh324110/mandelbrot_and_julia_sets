#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../util/util.h"

typedef struct {
  bool down : 1;
  bool last : 1;
  bool pressed : 1;
} Button;

typedef struct {
  Button buttons[GLFW_MOUSE_BUTTON_LAST];
  vec2s pos, delta;
  vec2s scroll, smooth_scroll;
  double zoom, smooth_zoom;
  GLFWcursor* arrow_cursor, * hand_cursor;
} Mouse;

typedef struct {
  Button keys[GLFW_KEY_LAST];
} Keyboard;

typedef void(*FWindow)();

typedef struct {
  GLFWwindow* handle;
  vec2s size;
  float aspect_ratio;
  FWindow init, destroy, update, render;
  Mouse mouse;
  Keyboard keyboard;

  double time;
  double last_time;
  double delta_time;
} Window;

extern Window window;

void window_loop(void);
void window_create(vec2s size, const char* title, FWindow init, FWindow destroy, FWindow update, FWindow render);
