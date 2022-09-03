/*
 *  Source code written by Gabriel Correia
*/

#include <malloc.h>
#include <assert.h>

#include "queue.h"

static int Q_default_on_create (void *unused, size_t unused_size)
{
    (void)unused;
    (void)unused_size;

	return 0;
}

static int Q_default_on_destroy (void *unused, size_t unused_size)
{
    (void)unused;
    (void)unused_size;

	return 0;
}

queue_t* queue_new ()
{
    queue_t *queue;
    
    queue = calloc (1, sizeof (queue_t));
    assert (queue);

    /* Using default callbacks functions instead of checking if every pointer is NULL or not */
    queue->on_create = Q_default_on_create;
    queue->on_destroy = Q_default_on_destroy;
    
    return queue;
}

static inline Q_node_t* Q_node_new (void *data)
{
    Q_node_t *qnew;
    
    qnew = calloc (1, sizeof (Q_node_t));
    assert (qnew);
    qnew->data = data;
    return qnew;
}

void queue_enqueue (void *data, queue_t *queue)
{
    assert (queue);

    queue->on_create (data, queue_size (queue));
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

    queue->on_destroy (data, 0);
    free (aux);
    return data;
}

size_t queue_size (queue_t *queue)
{
    size_t size = 0;
    Q_node_t *aux;
    assert (queue);

    aux = queue->head;
    if (!aux)
        return size;
    for (size = 1; (aux); size++) {
        if (aux->next)
            aux = aux->next;
        else
            break;
    }

    return size;
}

void queue_on_destroy (Q_callback callback, queue_t *queue)
{
    assert (queue);
    queue->on_destroy = callback;
}

void queue_on_create (Q_callback callback, queue_t *queue)
{
    assert (queue);
    queue->on_create = callback;
}

size_t queue_clear (queue_t *queue)
{
    Q_node_t *aux, *node;
    size_t size;
    assert (queue);

    aux = queue->head;
    for (size = 0; (aux); size++) {
        node = aux->next;
        /* Calling on_destroy before destroy the object */
        queue->on_destroy (aux->data, size);
        free (aux);
        aux = node;
    }

    queue->head = queue->tail = NULL;

    return size;
}


bool queue_is_full (queue_t *queue)
{
    return queue_size (queue);
}
bool queue_is_empty (queue_t *queue)
{
    return !queue_size (queue);
}

size_t queue_delete (queue_t *queue)
{
    size_t size;
    size = queue_clear (queue);

    free (queue);

    return size;
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

void queue_foreach_user (Q_user_callback callback, void *user, queue_t *queue)
{
    Q_node_t *aux;
    size_t pos;
    assert (queue);

    aux = queue->head;
    for (pos = 0; (aux); pos++) {
        if (callback (aux->data, user, pos))
            break;
        aux = aux->next;
    }
}

void* queue_select (size_t pos, queue_t *queue)
{
    Q_node_t *aux;
    void *data = NULL;
    assert (queue);

    aux = queue->head;
    for (size_t i = 0; (i < pos) && (aux); i++)
        aux = aux->next;

    if (aux)
        data = aux->data;

    return data;
}
