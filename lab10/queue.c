#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

node_t * initNode(int idx)
{
    node_t * nod = malloc (sizeof(node_t));
    nod->idx = idx;
    nod->next = nod->prev = NULL;

    return nod;
}

queue_t * initQueue()
{
    queue_t * q = malloc(sizeof(queue_t));

    q->len = 0;
    q->head = q->tail = NULL;

    return q;
}

int isQueueEmpty(queue_t * q)
{
    if (q->len == 0)
        return 1;
    return 0;
}

void enqueue(queue_t * q, int idx)
{
    node_t * nod = initNode(idx);

    if (q->len == 0)
        q->head = q->tail = nod;

    else
    {
        q->tail->next = nod;
        nod->prev = q->tail;
        q->tail = nod;
    }

    q->len++;
}

int dequeue(queue_t * q)
{
    node_t * nod = q->head;

    if (q->len == 1)
    {
        q->head = q->tail = NULL;
    }
    else
    {
        q->head = q->head->next;
    }
    q->len--;

    int idx = nod->idx;
    free(nod);

    return idx;
}

void remove_idx(queue_t *q, int idx)
{
    node_t * nod = q->head;
    
    if (q->len == 1)
    {
        if (q->head->idx = idx)
            {
                q->head = q->tail = NULL;
                q->len--;
            }
        return;
    }

    while (nod != NULL)
    {
        if (nod->idx = idx)
        {
            q->len--;
            nod->next->prev = nod->prev;
            nod->prev->next = nod->next;
            free(nod);
            return;
        }

        nod = nod->next;
    }
}