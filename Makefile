# Makefile

CC = gcc 
CPPFLAGS = `pkg-config --cflags sdl` -MMD
CFLAGS = -Werror -W -Wall -Wextra -std=c99 -O3
LDLIBS = `pkg-config --libs sdl` -lSDL_image
RM = rm -rf 
EXEC= segmentation
EXEC_TRAIN= segmentation_training
SRCS= main.c segmentation.c Matrix.c pixel_operations.c
SRCS_TRAIN= main_training.c segmentation_training.c matrix_training.c pixel_operations_training.c
OBJS= $(SRCS:.c=.o)
OBJS_TRAIN= $(SRCS_TRAIN:.c=.o)
all: $(EXEC) $(EXEC_TRAIN)


$(EXEC) : $(OBJS)
	$(CC)  $^ $(LDLIBS) -o $@

$(OBJS): $(SRCS) 
	$(CC)  $(CFLAGS) $(CPPFLAGS) -c $(SRCS) 

$(EXEC_TRAIN) : $(OBJS_TRAIN)
	$(CC)  $^ $(LDLIBS) -o $@

$(OBJS_TRAIN): $(SRCS_TRAIN) 
	$(CC)  $(CFLAGS) $(CPPFLAGS) -c $(SRCS_TRAIN)



clean:
	${RM} *.h.gch *.d segmentation segmentation_training a.out *.o *.dSYM *.txt


# END
