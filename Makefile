# Makefile

CC = gcc 
CPPFLAGS = -MMD `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0`
CFLAGS = -W -Werror -Wall -Wextra -std=c99 -O3
LDLIBS = -lm `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-3.0` -rdynamic
RM = rm -rf 
EXEC= application
SRCS= test.c
OBJS= test.o segmentation.o Matrix.o pixel_operations.o neural_network.o
all: $(EXEC) $(EXEC_TRAIN)


$(EXEC) : $(OBJS)
	$(CC)  $^ $(LDLIBS) -o $@

$(OBJS): $(SRCS) 
	$(CC)  $(CFLAGS) $(CPPFLAGS) -c $(SRCS) 

clean:
	${RM} *.h.gch *.d segmentation a.out *.dSYM


# END 	