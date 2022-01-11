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
class double_linked
{
public:
	double_linked<T>() : m_head (nullptr), m_last (nullptr) {};
	~double_linked<T>() 
	{
		linkedlist::node<T> *aux = m_head, *next = nullptr;
		while (aux) {
			next = aux->next;
			delete aux;
			aux = next;
		}
	}

	size_t empty ()
	{
		return !size ();
	}

	size_t size ()
	{
		linkedlist::node<T> *aux = m_head;
		size_t count = 0;

		while (aux) {
			aux = aux->next;
			count++;
		}
		return count;
	}

	void insert_at (const T data, const uintptr_t index)
	{
		linkedlist::node<T> *aux = nullptr, *index_node = m_head, 
			*next_aux = nullptr;

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
		linkedlist::node<T> *aux = nullptr;
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

	T pop_at (const uintptr_t index)
	{
		linkedlist::node<T> *pop = at (index), *next = nullptr, *prev = nullptr;
		T data{0};

		if (pop->next)
			next = pop->next;
		if (pop->prev)
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
		return pop_at (size () -1);
	}

	T pop_back (void)
	{
		return pop_at (0);
	}

	size_t for_each (void (*function)(T))
	{
		linkedlist::node<T> *aux = m_head;
		size_t count = 0;
		for (; count < size (); count++) {
			function (aux->data);
			aux = aux->next;
		}

		return count;
	}

	size_t for_each_reverse (void (*function)(T))
	{
		linkedlist::node<T> *aux = m_last;
		size_t node_count = size (), count = 0;
		for (; node_count > count; count++) {
			function (aux->data);
			aux = aux->prev;
		}

		return count;
	}

	node<T>* at (uintptr_t index) 
	{
		linkedlist::node<T> *index_node = m_head;

		for (; index; index--)
			if (index_node)
				if (index_node->next)
					index_node = index_node->next;
		assert (!index);

		return index_node;
	}

private:

	linkedlist::node<T> *m_head, *m_last;

};

}

