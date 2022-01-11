/*
 *  Source code written by Gabriel Correia
*/

#include <memory>
#include <iostream>

#define RANDOM_NUMBERS 0
#define NUMBERS_COUNT_BASE 10

#define VARIOUS_POP 1

#if RANDOM_NUMBERS
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#endif

#include "linked_list.hpp"

#if RANDOM_NUMBERS
constexpr unsigned RAN_MAX = 99999, RAN_NUMBERS_COUNT = 1000;
#endif

int main (void)
{
	auto int_values = std::make_shared<linkedlist::double_linked<int>> ();

#if RANDOM_NUMBERS
	/* Generating random numbers and inserting him at the linked list */
	boost::random::mt19937 random;
	boost::random::uniform_int_distribution<> six (0, RAN_MAX);
#else
	unsigned count = 0;
#endif

#if RANDOM_NUMBERS
	for (unsigned i = 0; i < RAN_NUMBERS_COUNT; i++)
		int_values->insert (six (random));
#else
	for (; count < NUMBERS_COUNT_BASE; count++)
		int_values->insert (count);
#endif

	int_values->pop_back ();

#if RANDOM_NUMBERS
	for (unsigned i = 0; i < RAN_NUMBERS_COUNT; i++)
		int_values->insert (six (random));
#else
	for (; count < NUMBERS_COUNT_BASE * 2; count++)
		int_values->insert (count);
#endif

	int_values->pop_front ();

#if RANDOM_NUMBERS
	for (unsigned i = 0; i < RAN_NUMBERS_COUNT; i++)
		int_values->insert_at (six (random), 10);
#else
	for (; count < NUMBERS_COUNT_BASE * 3; count++)
		int_values->insert (count);
#endif

#if VARIOUS_POP
	int_values->pop_front ();
	int_values->pop_front ();
	int_values->pop_front ();
	int_values->pop_back ();
	int_values->pop_back ();
	int_values->pop_back ();
#else
	int_values->pop_at (0);
	int_values->pop_at (20);
	int_values->pop_at (1);
#endif

	assert (!int_values->empty ());
	std::cout << "Linked list size: " << int_values->size () << std::endl;

	int_values->for_each_reverse ([] (auto data) {
		std::cout << data << std::endl;
	});

	return 0;
}

