# Makefile

CC = gcc 
CPPFLAGS = -MMD `pkg-config --cflags sdl`
CFLAGS = -W -std=c99  -O3 -flto
LDLIBS = -lm `pkg-config --libs sdl` -lSDL_image  -O3 -flto
RM = rm -rf 
EXEC= application
SRCS= main.c segmentation.c Matrix.c pixel_operations.c neural_network.c 
OBJS= $(SRCS:.c=.o)
all: $(EXEC) $(EXEC_TRAIN)


$(EXEC) : $(OBJS)
	$(CC)  $^ $(LDLIBS) -o $@

$(OBJS): $(SRCS) 
	$(CC)  $(CFLAGS) $(CPPFLAGS) -c $(SRCS) 

clean:
	${RM} *.h.gch *.d segmentation a.out *.o *.dSYM


# END
