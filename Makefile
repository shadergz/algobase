CC=gcc
CXX_COMPILER=g++
CPPFLAGS=-Wall -O1 -g

TEST_PROGRAMS=test-linkedlist test-queue test-hm

all: $(TEST_PROGRAMS)

test-hm: test-hm.cc
	$(CXX_COMPILER) -o $@ $^

test-linkedlist: test-linkedlist.cc
	$(CXX_COMPILER) -o $@ $^

test-queue: test-queue.c queue.c
	$(CC) -o $@ $^

%: %.cc
	$(CXX_COMPILER) $(CPPFLAGS) -o $@ $^

run: $(TEST_PROGRAMS)
	for program in $(TEST_PROGRAMS); do ./$$program; done

clean:
	-rm -f $(TEST_PROGRAMS)

.PHONY: all clean run

