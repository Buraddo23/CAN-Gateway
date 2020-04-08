CC = gcc

APP = gateway
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = 
LDFLAGS = -lpthread 

.PHONY: all clean run

all: $(APP)

$(APP): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
%.o: %.c $(SRCS:.c=.h) Makefile
	$(CC) -c -o $@ $<

clean:
	rm -f *.o $(APP) 

run: $(APP)
	./$(APP)
