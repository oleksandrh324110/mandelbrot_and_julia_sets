.PHONY: default-target all lib clean

default-target: all

ifndef target
$(error target is NOT defined)
endif

CFLAGS = -std=c11 -O0 -MMD -MP -Wall -Wextra -Wpedantic
CFLAGS += -Wno-unused-parameter
CFLAGS += -Ilib/glad/include -Ilib/glfw/include -Ilib/cglm/include
LDFLAGS = lib/glad/src/gl.o lib/glfw/src/libglfw3.a -Ilib/cglm/libcglm.a -lm

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

lib:
	cd lib/glfw && $(CMAKEFLAGS) cmake . && make
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