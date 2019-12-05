# Makefile

#CC = gcc \
#CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3 -rdynamic
#LDLIBS = `pkg-config --libs gtk+-3.0`

#EXE = test segmentation Matrix 

#all: $(EXE)

#$(foreach f, $(EXE), $(eval $(f):))

#.PHONY: clean

#clean:
#	${RM} $(EXE) main
# END

CC=gcc
CFLAGS=-W -Wall -Wextra -Werror `pkg-config --cflags gtk+-3.0` -O3 -rdynamic
LDFLAGS= `pkg-config --libs gtk+-3.0`
EXEC= test
SRCS = test.c
OBJS=$(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS): $(SRCS)
	$(CC) -c $? $(CFLAGS)

clean:
	rm -rvf *~
	rm -rvf \#*
	rm -rvf $(OBJS)

fclean: clean
	rm -rvf $(EXEC)

re: fclean $(EXEC)