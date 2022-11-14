#include <stdio.h>
#include <stdlib.h>

typedef struct nodeAdjList {
    size_t size; /**< Num˘arul de vecini */
    size_t capacity; /**< Capacitatea total˘a a vectorului */
    size_t *neighbours; /**< Vectorul de adiacent, ˘a */
} nodeAdjList_t;


typedef struct graphAdjList 
{
    size_t v; /**< Num˘arul de noduri din graf */
    nodeAdjList_t **adjList; /**< Lista de adiacent, ˘a */
} graphAdjList_t;

void inserare_muchie(graphAdjList_t * g, int i, int j)
{
    if (g->adjList[i]->size == g->adjList[i]->capacity)
        {
            g->adjList[i]->capacity += 3;
            g->adjList[i]->neighbours = realloc (g->adjList[i]->neighbours, g->adjList[i]->capacity * sizeof(size_t));
        }

    if (g->adjList[j]->size == g->adjList[j]->capacity)
        {
            g->adjList[j]->capacity += 3;
            g->adjList[j]->neighbours = realloc (g->adjList[j]->neighbours, g->adjList[j]->capacity * sizeof(size_t));
        }

    g->adjList[i]->neighbours[g->adjList[i]->size++] = j;
    g->adjList[j]->neighbours[g->adjList[j]->size++] = i;

    return;
}

void stergere_muchie(graphAdjList_t *g, int i, int j)
{
    int idx=0;
    while (g->adjList[i]->neighbours[idx] != j) 
        idx++;

    for (int k=idx;k<g->adjList[i]->size-1;k++)
        g->adjList[i]->neighbours[k] = g->adjList[i]->neighbours[k+1];
    g->adjList[i]->size--;

    idx=0;
    while (g->adjList[j]->neighbours[idx] != i) 
        idx++;

    for (int k=idx;k<g->adjList[j]->size-1;k++)
        g->adjList[j]->neighbours[k] = g->adjList[j]->neighbours[k+1];
    g->adjList[j]->size--;

    return;
}

int grad(graphAdjList_t *g, int nod)
{
    return g->adjList[nod]->size;
}

int main()
{
    int v,e;
    scanf("%d%d",&v,&e);

    graphAdjList_t * g = malloc (sizeof(graphAdjList_t));
    g->v = v;
    g->adjList = malloc (v * sizeof(nodeAdjList_t*));
    
    for (int i=0;i<v;i++)
    {
        g->adjList[i] = malloc (sizeof(nodeAdjList_t));
        g->adjList[i]->capacity = 3;
        g->adjList[i]->size = 0;
        g->adjList[i]->neighbours = malloc (3 * sizeof(size_t));
    }

    int v1,v2;
    for(int i=0;i<e;i++)
    {
        scanf("%d%d",&v1,&v2);
        inserare_muchie(g,v1,v2);
    }

    for (int i=0;i<v;i++)
    {
        printf("%d : ",i);

        for (int j=0;j<g->adjList[i]->size;j++)
            printf("%d ",g->adjList[i]->neighbours[j]);
        printf("\n");
    }
    
    printf("\nGrad 1: %d\nGrad 2: %d\n\n",grad(g,1),grad(g,2));

    stergere_muchie(g,0,2);
    stergere_muchie(g,1,0);

        for (int i=0;i<v;i++)
    {
        printf("%d : ",i);

        for (int j=0;j<g->adjList[i]->size;j++)
            printf("%d ",g->adjList[i]->neighbours[j]);
        printf("\n");
    }

        for (int i=0;i<v;i++)
    {
        free(g->adjList[i]->neighbours);
        free(g->adjList[i]);
    }

    free(g->adjList);

    free(g);

    return 0;
}