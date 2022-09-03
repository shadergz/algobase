#include <stdio.h>

#include "queue.h"

static int display_numbers (void *data, size_t position)
{
    printf ("Position = %zu : Value = %d\n", position, *((int*)data));
    return 0;
}

static int at_enqueue (void *data, size_t queue_len)
{
    printf ("The value %d will be push into queue at %ld position\n", *((int*)data), queue_len);
    return 0;
}

static int at_dequeue (void *data, size_t pos)
{
    printf ("The value %d at position %ld will be deleted\n", *((int*)data), pos);
    return 0;
}

int main (void)
{
    static int numbers[] = {12, 43, 234, 65, 2, 56, 34, 643, 3, 12, 52, 42, 52, 7725, 526,45, 256, 1};

	(void)numbers;

    queue_t *main_queue = queue_new ();
    
    /* Setting functions callback */
    queue_on_create (at_enqueue, main_queue);
    queue_on_destroy (at_dequeue, main_queue);

    for (int i = 0; i < sizeof (numbers) / sizeof (int); i++)
        queue_enqueue (&numbers[i], main_queue);

    for (int i = 0; i <= 2; i++)
        printf ("Some value: %d\n", *((int*)queue_dequeue (main_queue)));

    queue_foreach (display_numbers, main_queue);
    queue_delete (main_queue);

    return 0;
}