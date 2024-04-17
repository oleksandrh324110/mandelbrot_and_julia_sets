#include "window.h"

#include <stdio.h>
#include <stdlib.h>

Window window;

static void _size_callback(GLFWwindow* handle, int width, int height) {
	window.size = (ivec2s){{ width, height }};
	glViewport(0, 0, width, height);
}

static void _cursor_callback(GLFWwindow* handle, double x, double y) {
	window.mouse.delta = glms_vec2_sub(window.mouse.position, (vec2s) { { x, y } });
	window.mouse.delta.x *= -1;
	window.mouse.position = (vec2s){{ x, y }};
}

static void _key_callback(GLFWwindow* handle, int key, int scancode, int action, int mods) {
	Button* button = &window.keyboard.buttons[key];
	button->down = action != GLFW_RELEASE;
	button->pressed = button->down && !button->last;
	button->last = button->down;
}

static void _mouse_callback(GLFWwindow* handle, int button, int action, int mods) {
	Button* b = &window.mouse.buttons[button];
	b->down = action != GLFW_RELEASE;
	b->pressed = b->down && !b->last;
	b->last = b->down;
}

static void _error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW error %d:%s\n", error, description);
}

void window_create(int width, int height, const char* title, FWindow init, FWindow destroy, FWindow update, FWindow render) {
	window.init = init;
	window.destroy = destroy;
	window.update = update;
	window.render = render;

	window.last_frame = glfwGetTime();
	window.last_second = glfwGetTime();

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(1);
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwSetErrorCallback(_error_callback);

	window.size = (ivec2s){{ width, height }};

	window.handle = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window.handle) {
		fprintf(stderr, "Failed to create window\n");
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window.handle);

	if (!gladLoadGL(glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		glfwTerminate();
		exit(1);
	}

	glfwSetWindowSizeCallback(window.handle, _size_callback);
	glfwSetCursorPosCallback(window.handle, _cursor_callback);
	glfwSetKeyCallback(window.handle, _key_callback);
	glfwSetMouseButtonCallback(window.handle, _mouse_callback);

	glfwSwapInterval(1);
}

void window_loop(void) {
	window.init();

	while (!glfwWindowShouldClose(window.handle)) {
		double now = glfwGetTime();

		window.frame_delta = now - window.last_frame;
		window.last_frame = now;

		if (now - window.last_second >= 1.0) {
			window.fps = window.frames;
			window.frames = 0;
			window.last_second = now;
		}

		window.frames++;
		window.update();
		window.render();

		glfwSwapBuffers(window.handle);
		glfwPollEvents();
	}

	window.destroy();
	glfwTerminate();
	exit(0);
}
