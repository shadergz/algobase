CC=gcc
CPPC=g++
CPPFLAGS=-Wall -O1 -g

all: test_linked_list test_queue

test_linked_list: test_linked_list.cc
	$(CPPC) $(CPPFLAGS) -o $@ $^

test_queue: test_queue.c queue.c
	$(CC) -o $@ $^ 

clean:
	-rm -f test_linked_list test_queue

.PHONY: all clean
