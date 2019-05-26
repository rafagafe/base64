
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -I../

src  = $(wildcard *.c)
src += $(wildcard ../*.c)
obj  = $(src:.c=.o)
dep  = $(obj:.o=.d) 

.PHONY: build all clean test

build: unit-test

clean:
	rm -rf $(dep)
	rm -rf $(obj)
	rm -rf unit-test
	
all: clean build

test: unit-test
	./unit-test

unit-test: $(obj)
	gcc $(CFLAGS) -o $@ $^

-include $(dep)

%.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@
