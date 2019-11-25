# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Werror -W -Wextra -Wall -std=c99 -O0
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: main

main: main.o display.o segmentation.o Matrix.o 

clean:
	${RM} *.o
	${RM} *.d

fclean: clean
	${RM} main

# END