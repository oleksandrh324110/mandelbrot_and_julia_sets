default-target: all

ifndef target
$(error target is NOT defined)
endif

CFLAGS = -std=c11 -O0 -MMD -MP -Wall -Wextra -Wpedantic
CFLAGS += -Wno-unused-parameter
CFLAGS += -Ilib/glfw/include -Ilib/cglm/include -Ilib/glad/include
LDFLAGS = lib/glfw/src/libglfw3.a lib/cglm/libcglm.a lib/glad/src/gl.o -lm

ifeq ($(target), linux)
	CC = gcc
	CFLAGS +=
	LDFLAGS +=
else ifeq ($(target), darwin)
	CC = clang
	CFLAGS +=
	LDFLAGS += -framework Cocoa -framework IOKit -framework QuartzCore
	GLFW_CMAKE_FLAGS = -DCMAKE_OSX_DEPLOYMENT_TARGET=$(shell sw_vers -productVersion | cut -c 1-2)
endif

SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

.PHONY: default-target all lib clean

all: compile link run

lib:
	cd lib/glfw && cmake . $(GLFW_CMAKE_FLAGS) && make
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make
	cd lib/glad && $(CC) -c src/gl.c -o src/gl.o -Iinclude

compile: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

link:
	$(CC) $(OBJ) -o ./bin/main.exe $(LDFLAGS)

run:
	./bin/main.exe

clean:
	rm $(OBJ) $(DEP)

-include $(DEP)

