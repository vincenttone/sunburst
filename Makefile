CC=gcc
CFLAGS=-g
VPATH=src
sources:=test.c list.c
objects:=$(sources:%.c=output/%.o)
.PHONY: all output_dir
all: output_dir $(objects)
	$(CC) -o output/test $(objects)
$(objects): output/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
output_dir:
	@if [ ! -d output ];then mkdir output;fi
.PHONY: clean
clean:
	@rm -rf output
