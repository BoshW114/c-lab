CC     = gcc
CFLAGS = -Wall -Wextra -std=c17 -g

all: dynarray.exe test_dynarray.exe

dynarray.exe: dynarray.o main.o
	$(CC) $(CFLAGS) -o $@ $^

test_dynarray.exe: dynarray.o test_dynarray.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c dynarray.h
	$(CC) $(CFLAGS) -c $< -o $@

test_dynarray.o: test_dynarray.c dynarray.h test_util.h
	$(CC) $(CFLAGS) -c $< -o $@

test: test_dynarray.exe
	./test_dynarray.exe

clean:
	del /Q *.o *.exe

.PHONY: all test clean
