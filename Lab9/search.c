#include <stdio.h>
#include <stdlib.h>
#include "search.h"

void dfs(graphMat_t * g, int *viz, int idx)
{   
    printf("%d ",idx);
    viz[idx] = 1;

    for (int i=0;i<g->v;i++)
    {
        if (g->mat[idx][i] == 1 && viz[i]==0)
            dfs(g,viz,i);
    }

}

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

void bfs(graphMat_t * g, int *viz, int start)
{
    queue_t * q = initQueue();

    enqueue(q,start);
    viz[start] = 1;
    while(!isQueueEmpty(q))
    {
        int idx = dequeue(q);
        printf("%d ",idx);

        for (int i=0;i<g->v;i++)
        {
            if (g->mat[idx][i] == 1 && viz[i] == 0)
                {
                    enqueue(q,i);
                    viz[i] = 1;
                }
        }
    }
}

int has_cycle(graphMat_t * g, int *viz, int start, int prev)
{
    viz[start] = 1;
    int ok = 0;

    for (int i=0;i<g->v;i++)
    {
        if (i == prev)
            continue;

        if (g->mat[start][i] == 1 && viz[i] == 1)
            return 1;

        else if (g->mat[start][i] == 1 && viz[i] == 0)
            if (has_cycle(g,viz,i,start) == 1) ok=1;
    }

    return ok;

}

