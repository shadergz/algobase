/*
 *  Source code written by Gabriel Correia
*/

#pragma once

#include <algorithm>
#include <cstdint>
#include <cassert>

namespace linkedlist {

template<typename T>
struct node {
	node<T> *next, *prev;
	T data;
};

template<typename T>
class doubly_linked
{
public:
	doubly_linked<T>() : m_head (nullptr), m_last (nullptr) {};
	~doubly_linked<T>() 
	{
		node<T> *aux = m_head, *next = nullptr;
		while (aux) {
			next = aux->next;
			delete aux;
			aux = next;
		}
	}

	bool empty ()
	{
		return !size ();
	}

	size_t size ()
	{
		node<T> *aux = m_head;
		size_t count = 0;

		while (aux) {
			aux = aux->next;
			count++;
		}
		return count;
	}

	void insert_at (const T data, const uintptr_t index)
	{
		node<T> *aux = nullptr, *index_node = m_head, *next_aux = nullptr;

		assert ((aux = new node<T>));
		aux->data = data;
		aux->next = aux->prev = nullptr;

		index_node = at (index);

		if (index_node->next)
			next_aux = index_node->next;
		index_node->next = aux;
		aux->prev = index_node;
		aux->next = next_aux;
		aux->next->prev = aux;

	}

	void insert (const T data)
	{
		node<T> *aux = nullptr;
		assert ((aux = new node<T>));
		aux->data = data;
		aux->next = aux->prev = nullptr;

		if (!m_head) {
			m_last = m_head = aux;
		} else if (m_last) {
			m_last->next = aux;
			aux->prev = m_last;
			m_last = aux;
		}
	}

	node<T>* search (T data)
	{
		node<T> *hand = m_head;
		while (hand) {
			if (hand->data == data) break;
			if (hand->next) hand = hand->next;
			else assert (hand->next);
		}
		return hand;
	}

	T pop_at (const uintptr_t index)
	{
		node<T> *pop = at (index);
		return pop_node (pop);
	}

	T pop_node (node<T> *pop)
	{
		assert (pop);

		node<T> *next = nullptr, *prev = nullptr;
		T data{0};

		next = pop->next;
		prev = pop->prev;

		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
		
		if (pop == m_head)
			m_head = next;
		if (pop == m_last)
			m_last = prev ? prev : m_head;
		
		data = pop->data;
		delete pop;

		return data;
	}

	T pop_front (void)
	{
		return pop_at (size () - 1);
	}

	T pop_back (void)
	{
		return pop_at (0);
	}

	size_t for_each (void (*function)(T))
	{
		node<T> *aux = m_head;
		size_t count = 0;
		for (; count < size (); count++) {
			function (aux->data);
			aux = aux->next;
		}

		return count;
	}

	size_t for_each_reverse (void (*function)(T))
	{
		node<T> *aux = m_last;
		size_t node_count = size (), count = 0;
		for (; node_count > count; count++) {
			function (aux->data);
			aux = aux->prev;
		}

		return count;
	}

	uintptr_t pos (node<T>* curr)
	{
		assert (curr);

		node<T> *aux = m_head;
		size_t pos = -1;
		for (size_t i = 0; (aux); i++) {
			if (aux == curr) pos = i;
			aux = aux->next;
		}

		assert (pos != -1);

		return pos;
	}

	T get (node<T> *from)
	{
		assert (from);
		return from->data;
	}

	node<T>* at (uintptr_t index) 
	{
		node<T> *index_node = m_head;

		for (; index; index--)
			if (index_node)
				if (index_node->next)
					index_node = index_node->next;
		assert (!index);

		return index_node;
	}

private:

	node<T> *m_head, *m_last;

};

}

