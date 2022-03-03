# algobase

A collection of data structure written in various languages and SFW to use

## Linked List

### Doubly Linked List

- Most specifically recognized to have two nodes: next and previous

- Operations available: Insertion / Deletion / Selection / "For each" operations

Usage example:

> Declaring a Double Linked List of double values

```cc
auto double_values = std::make_shared<linkedlist::doubly_linked<double>> ();
double_values->insert (4.2E6);
double_values->insert (2.2E2);
auto value = double_values->pop_front (1.3E5);
assert (double_values->size ());

/* Doesn't need of deletion (The smart pointer does it by himself) */
```

> See more in 'test_linked_list.cc'

## Queue

A FIFO linked list based algorithm

Usage example:

```c
static int numbers[] = {12, 43, 234, 65, 2, 56, 34, 643, 3, 12, 52, 42, 52, 7725, 526,45, 256, 1};
queue_t *main_queue = queue_new ();
for (int i = 0; i < sizeof (numbers) / sizeof (int); i++)
    queue_enqueue (&numbers[i], main_queue);

for (int i = 0; i <= 2; i++)
    printf ("Some values: %d\n", *(int*)queue_dequeue (main_queue));

queue_foreach (display_numbers, main_queue);
queue_delete (main_queue);
```

> Check the impl source code in 'queue.c'

## Hashmap

```cc
hashmap gabriel;
    gabriel.insert ("Name", "Gabriel Correia");
    gabriel.insert ("ID", "10010219");
    gabriel.insert ("DEV", "Maybe :)");
    
    std::cout << "User Name: " << gabriel["Name"] << std::endl;
    std::cout << "User ID: " << gabriel["ID"] << std::endl;
    std::cout << "Is user a developer? " << gabriel["DEV"] << std::endl;
```
