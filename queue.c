/*
 *  Source code written by Gabriel Correia
*/

#include <malloc.h>
#include <assert.h>

#include "queue.h"

queue_t* queue_new ()
{
    queue_t *queue;
    
    queue = calloc (sizeof (queue_t), 1);
    assert (queue);
    
    return queue;
}

static inline Q_node_t* Q_node_new (void *data)
{
    Q_node_t *new;
    
    new = calloc (sizeof (Q_node_t), 1);
    assert (new);
    new->data = data;
    return new;
}

void queue_enqueue (void *data, queue_t *queue)
{
    assert (queue);
    if (queue->tail) {
        queue->tail->next = Q_node_new (data);
        queue->tail = queue->tail->next;
    } else {
        queue->tail = queue->head = Q_node_new (data);
    }
}

void* queue_dequeue (queue_t *queue)
{
    Q_node_t *aux = NULL;
    void *data = NULL;

    assert (queue);
    if (queue->head) {
        data = queue->head->data;
        aux = queue->head;
        queue->head = aux->next;
        if (!queue->head) {
            queue->tail = queue->head;
        }
    }

    free (aux);
    return data;
}

size_t queue_size (queue_t *queue)
{
    size_t size;
    Q_node_t *aux;
    assert (queue);

    aux = queue->head;
    for (size = 0; (aux); size++) {
        if (aux->next)
            aux = aux->next;
    }

    return size;
}

void queue_delete (queue_t *queue)
{
    Q_node_t *aux, *node;
    assert (queue);

    aux = queue->head;
    for (; (aux); ) {
        node = aux->next;
        free (aux);
        aux = node;
    }

    free (queue);
}

void queue_foreach (Q_callback callback, queue_t *queue)
{
    Q_node_t *aux;
    size_t pos;
    assert (queue);

    aux = queue->head;
    for (pos = 0; (aux); pos++) {
        if (callback (aux->data, pos))
            break;
        aux = aux->next;
    }
}
