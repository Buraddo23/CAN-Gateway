CC = gcc

APP = gateway
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

.PHONY: all clean run

all: $(APP)

$(APP): $(OBJS)
	$(CC) -o $@ $^
	
%.o: %.c $(SRCS:.c=.h) Makefile
	$(CC) -c -o $@ $<

clean:
	rm -f *.o $(APP) 

run: $(APP)
	./$(APP)
