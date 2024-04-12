#include <stdio.h>

#include "gfx/window.h"

void init() {

}

void destroy() {

}

void tick() {

}

void update() {

}

void render() {

}

int main(void) {
  window_create(800, 600, "Hello, World!", init, destroy, tick, update, render);
  window_loop();
  return 0;
}
