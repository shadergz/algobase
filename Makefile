CC=gcc
CPPC=g++
CPPFLAGS=-Wall -O1 -g

TEST_PROGRAMS=test_linked_list test_queue test_hm

all: $(TEST_PROGRAMS)

%: %.c
	$(CC) -o $@ $^

test_queue: test_queue.c queue.c
	$(CC) -o $@ $^

%: %.cc
	$(CPPC) $(CPPFLAGS) -o $@ $^

run: $(TEST_PROGRAMS)
	for program in $(TEST_PROGRAMS); do ./$$program; done

clean:
	-rm -f $(TEST_PROGRAMS)

.PHONY: all clean
