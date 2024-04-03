default-target: all
.PHONY: default-target

ifndef target
$(error target is NOT defined)
endif

CFLAGS = -std=c11 -O0 -Wall -Wextra -Wpedantic -Wno-unused-parameter -MMD -MP
CFLAGS += -Ilib/glad/include -Ilib/glfw/include
LDFLAGS = lib/glad/src/gl.o lib/glfw/src/libglfw3.a -lm

ifeq ($(target), linux)
	CC = gcc
	CFLAGS +=
	LDFLAGS +=
else ifeq ($(target), darwin)
	CC = clang
	CFLAGS +=
	LDFLAGS += -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo
endif

SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.cpp=.d)

all: compile link run

lib:
	cd lib/glfw && cmake . && make
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
.PHONY: clean

-include $(DEP)