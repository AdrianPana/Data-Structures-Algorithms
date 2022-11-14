#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

typedef struct graphMat 
{
    size_t v; /**< Num˘arul de noduri din graf */
    int **mat; /**< Matricea de adiacent, ˘a */
} graphMat_t;

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

void dfs(graphMat_t * g, int *viz, int idx);

void bfs(graphMat_t * g, int *viz, int start);

int has_cycle(graphMat_t * g, int *viz, int start, int prev);

#endif