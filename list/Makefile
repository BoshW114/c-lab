CC     = gcc
CFLAGS = -Wall -Wextra -std=c17 -g

all: list_demo test_list

list_demo: list.o main.o
	$(CC) $(CFLAGS) -o $@ $^

test_list: list.o test_list.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c list.h
	$(CC) $(CFLAGS) -c $< -o $@

test_list.o: test_list.c list.h ../dynarray/test_util.h
	$(CC) $(CFLAGS) -c $< -o $@

test: test_list
	./test_list

clean:
	rm -f *.o list_demo test_list