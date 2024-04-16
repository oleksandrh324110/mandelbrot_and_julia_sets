#include <stdio.h>

#include "gfx/window.h"
#include "state.h"

State state;

void init(void) {
  state.window = &window;
}

void destroy(void) {

}

void update(void) {

}

void render(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(window.mouse.position.x / window.size.x, window.mouse.position.x / window.size.x, window.mouse.position.x / window.size.x, 1);
}

int main(void) {
  window_create(720, 480, "Hello, World!", init, destroy, update, render);
  window_loop();
}
