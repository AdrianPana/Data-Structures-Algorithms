#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

typedef struct node
{
    int idx;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct queue
{
    int len;
    node_t *head;
    node_t *tail;
} queue_t;

node_t * initNode(int idx);

queue_t * initQueue();

int isQueueEmpty(queue_t * q);

void enqueue(queue_t * q, int idx);

int dequeue(queue_t * q);

void remove_idx(queue_t *q, int idx);

#endif