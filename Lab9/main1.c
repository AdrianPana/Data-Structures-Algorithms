#include <stdio.h>
#include <stdlib.h>
#include "search.h"

void inserare_muchie(graphMat_t * graph, int i, int j)
{
    graph->mat[i][j] = graph->mat[j][i] = 1;
}

void stergere_muchie(graphMat_t * graph, int i, int j)
{
    graph->mat[i][j] = graph->mat[j][i] = 0;
}

int grad(graphMat_t * graph, int nod)
{
    int nr = 0;
    for (int i=0;i<graph->v;i++)
        if (graph->mat[nod][i] == 1) nr++;

    return nr;
}

int main()
{
    int v,e;
    scanf("%d%d",&v,&e);

    graphMat_t * graph = malloc (sizeof(graphMat_t));
    graph->v = v;

    graph->mat = calloc (v , sizeof(int*));
    for (int i=0;i<v;i++)
        graph->mat[i] = calloc (v , sizeof(int));

    int v1,v2;
    for (int i=0;i<e;i++)
    {
        scanf("%d%d",&v1,&v2);
        inserare_muchie(graph,v1,v2);
    }

    for (int i=0;i<v;i++)
    {
        for (int j=0;j<v;j++)
            printf("%d ",graph->mat[i][j]);
        printf("\n");
    }

    int *viz = calloc (v , sizeof(int));

    if (has_cycle(graph,viz,0,0))
        printf("Are cicluri\n");
    else printf("Nu are cicluri\n");

    for (int i=0;i<v;i++)
    viz[i] = 0;

    printf("\nParcurgere DFS: ");
    dfs(graph,viz,0);

    for (int i=0;i<v;i++)
        viz[i] = 0;

    printf("\nParcurgere BFS: ");
    bfs(graph,viz,0);

    printf("\nGrad 1: %d\nGrad 2: %d\n\n",grad(graph,1),grad(graph,2));

    stergere_muchie(graph,0,2);
    stergere_muchie(graph,3,2);

    for (int i=0;i<v;i++)
    {
        for (int j=0;j<v;j++)
            printf("%d ",graph->mat[i][j]);
        printf("\n");
    }
    
    for (int i=0;i<v;i++)
    viz[i] = 0;

    if (has_cycle(graph,viz,0,0))
        printf("Are cicluri\n");
    else printf("Nu are cicluri\n");

    free(viz);

    for (int i=0;i<v;i++)
    free(graph->mat[i]);

    free(graph->mat);

    free(graph);
}
