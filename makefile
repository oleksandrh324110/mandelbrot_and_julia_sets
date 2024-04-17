.PHONY: default-target all libs clean

default-target: all

ifndef target
$(error target is NOT defined)
endif

CFLAGS = -std=c11 -O0 -MMD -MP
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -Wno-unused-parameter
CFLAGS += -Ilibs/glad/include -Ilibs/glfw/include -Ilibs/cglm/include
LDFLAGS = libs/glad/src/gl.o libs/glfw/src/libglfw3.a -Ilibs/cglm/libcglm.a -lm

ifeq ($(target), linux)
	CC = gcc
	CFLAGS +=
	LDFLAGS +=
else ifeq ($(target), darwin)
	CC = clang
	CFLAGS +=
	LDFLAGS += -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo
	CMAKEFLAGS += MACOSX_DEPLOYMENT_TARGET=14.0
endif

SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: compile link run

libs:
	cd libs/glfw && $(CMAKEFLAGS) cmake . && make
	cd libs/cglm && cmake . -DCGLM_STATIC=ON && make
	cd libs/glad && $(CC) -c src/gl.c -o src/gl.o -Iinclude

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