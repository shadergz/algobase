CPPC=g++
CPPFLAGS=-Wall -O2

all: test_linked_list

test_linked_list: test_linked_list.cc
	$(CPPC) $(CPPFLAGS) -o $@ $^

clean:
	-rm -f test_linked_list

.PHONY: all clean
