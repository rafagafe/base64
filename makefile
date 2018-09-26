

build: example-01.exe example-02.exe

clean:
	rm -rf *.o
	rm -rf *.exe

all: clean build

test: test.exe
	./test.exe

example-01.exe: example-01.o base64.o
	gcc -o example-01.exe example-01.o base64.o

example-02.exe: example-02.o base64.o
	gcc -o example-02.exe example-02.o base64.o

test.exe: test.o base64.o
	gcc -o test.exe test.o base64.o

base64.o: base64.c base64.h
	gcc -std=c99 -c base64.c

example-01.o: example-01.c base64.h
	gcc -std=c99 -c example-01.c

example-02.o: example-02.c base64.h
	gcc -std=c99 -c example-02.c

test.o: test.c base64.h
	gcc -std=c99 -c test.c
