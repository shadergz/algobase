# algobase

A collection of data structure written in various languages and SFW to use

## Linked List

### Double Linked List

- Most specifically recognized to have two nodes: next and previous

- Operations available: Insertion / Deletion / Selection / "For each" operations

Usage example:

> Declaring a Double Linked List of double values

```cpp
auto double_values = std::make_shared<linkedlist::double_linked<double>>();
double_values->insert (4.2E10);
double_values->insert (2.2E2)
double_values->pop_front (1.3E5);
assert (double_values->size ());

/* Doesn't need of deletion (The smart pointer does it by himself) */
```

> See more in 'test_linked_list.cc'
