
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -I../

src  = $(wildcard *.c)
src += $(wildcard ../*.c)
obj  = $(src:.c=.o)
dep  = $(obj:.o=.d) 

.PHONY: build all clean

build: example-01 example-02

all: clean build

clean:
	rm -rf $(obj)
	rm -rf $(dep)
	rm -rf example-01 example-02

example-01: example-01.o ../base64.o
	gcc $(CFLAGS) -o $@ $^

example-02: example-02.o ../base64.o
	gcc $(CFLAGS) -o $@ $^

-include $(dep)

%.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@
