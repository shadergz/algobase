CC=gcc
CPPC=g++
CPPFLAGS=-Wall -O1 -g

TEST_PROGRAMS=test-linkedlist test-queue test-hm

all: $(TEST_PROGRAMS)

%: %.c
	$(CC) -o $@ $^

test-queue: test-queue.c queue.c
	$(CC) -o $@ $^

%: %.cc
	$(CPPC) $(CPPFLAGS) -o $@ $^

run: $(TEST_PROGRAMS)
	for program in $(TEST_PROGRAMS); do ./$$program; done

clean:
	-rm -f $(TEST_PROGRAMS)

.PHONY: all clean run

