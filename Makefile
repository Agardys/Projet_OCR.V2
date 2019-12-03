# Simple SDL mini Makefile

CC=gcc
 
CPPFLAGS= `sdl-config --libs` #`pkg-config --cflags sdl` #-MMD #`sdl-config --cflags` -lSDL_ttf
CFLAGS= -Werror -W -Wextra -Wall -std=c99 -O0
LDFLAGS= `pkg-config --libs sdl` -lSDL_image -lSDL
LDLIBS= 

all: main

main: main.o display.o segmentation.o Matrix.o 

clean:
	${RM} *.o
	${RM} *.d

fclean: clean
	${RM} main

# END