CC=gcc
CFLAGS=-g
VPATH=src
sources=test.c list.c
objects:=$(sources:%.c=output/%.o)
.PHONY: all
all: $(objects)
	$(CC) -o test $(objects)
$(objects): $(sources)
	$(CC) -c $(CFLAGS) $< -o $@
.PHONY: clean
clean:
	-rm *.o
