#include <stdio.h>
#include <stdlib.h>
#include "graph_adj_matrix.h"
#include "stack.h"
#include <limits.h>

#define INF 999999

int DFS(graphAdjMat_t * m, int nod, int *v, stack_t * stack)
{
    v[nod] = 1;
    for (int i=0;i<m->numNodes;i++)
    {
    if (m->mat[nod][i]!=0 && v[i]==0)
        {   
            return DFS(m,i,v,stack);
        }
    }
    push(stack,nod);
}

void topologial_sort(graphAdjMat_t * m)
{
    stack_t * stack = initStack();

    int * v = calloc (m->numNodes, sizeof(int));

    for (int i=0;i<m->numNodes;i++)
    {
        if (v[i] == 1)
            continue;

        DFS(m,i,v,stack);
    }

    while(top(stack)!=-1)
    {
        int nod = pop(stack);
        printf("%d ",nod);
    }

    free(v);
}

void Floyd_Warshall(graphAdjMat_t * m, graphEdge_t * vert, int e)
{
    int **d = malloc (m->numNodes * sizeof(*d));
    for (int i=0;i<m->numNodes;i++)
        d[i] = calloc (m->numNodes, sizeof(**d));

    for (int i=0;i<m->numNodes;i++)
    for (int j=0;j<m->numNodes;j++)
        d[i][j] = INF;

    for (int i=0;i<e;i++)
    {
        d[vert[i].u][vert[i].v] = vert[i].cost;
    }
    for (int i=0;i<e;i++)
    {
        d[vert[i].v][vert[i].v] = 0;
    }

    for (int k=0;k<m->numNodes;k++)
    for (int i=0;i<m->numNodes;i++)
    for (int j=0;j<m->numNodes;j++)
    {
        if (d[i][j] > d[i][k] + d[k][j])
            d[i][j] = d[i][k] + d[k][j];
    }
    for (int i=0;i<m->numNodes;i++)
    for (int j=0;j<m->numNodes;j++)
    {
        printf("%d %d -> %d\n", i,j,d[i][j]);
    }
    
    for (int i=0;i<m->numNodes;i++)
        free(d[i]);
    free(d);
}

void Bellman_Ford(graphAdjMat_t * m, graphEdge_t * vert, int e)
{
    int **d = malloc (m->numNodes * sizeof(*d));
    for (int i=0;i<m->numNodes;i++)
        d[i] = calloc (m->numNodes, sizeof(**d));
    
    for (int i=0;i<m->numNodes;i++)
    for (int j=0;j<m->numNodes;j++)
        d[i][j] = INF;

    for (int i=0;i<m->numNodes;i++)
    {
        d[i][i] = 0;
    }

    for (int j=0;j<m->numNodes;j++)
    for (int pas=0;pas<m->numNodes-1;pas++)
    {
        for (int i=0;i<e;i++)
        {
            if (d[j][vert[i].v] > d[j][vert[i].u] + vert[i].cost)
                d[j][vert[i].v] = d[j][vert[i].u] + vert[i].cost;
        }
    }

    for (int j=0;j<m->numNodes;j++)
    {
        for (int i=0;i<e;i++)
        {
            if (d[j][vert[i].v] > d[j][vert[i].u] + vert[i].cost)
            {
                printf("Ciclu infinit\n");
                return;
            }
        }
    }

    for (int i=0;i<m->numNodes;i++)
    for (int j=0;j<m->numNodes;j++)
    {
        printf("%d %d -> %d\n", i,j,d[i][j]);
    }
    
    for (int i=0;i<m->numNodes;i++)
        free(d[i]);
    free(d);
}

void dijkstra(graphAdjMat_t * m, graphEdge_t * vert, int e, int nod)
{
    int *v = calloc (m->numNodes , sizeof(int));
    int *d = calloc (m->numNodes , sizeof(int));
    
    for (int i=0;i<m->numNodes;i++)
        d[i] = INF;

    d[nod] = 0;

    for (int i=0;i<e;i++)
    {
        if (m->mat[nod][i] != 0)
            d[i] = m->mat[nod][i];
    }
        v[nod]=1;

        for (int j=0;j<m->numNodes;j++)
        {
            int min = INF;
            int idx = -1;

            for (int k=0;k<m->numNodes;k++)
            {   
                if (min > d[k] && v[k] == 0)
                {
                    min = d[k];
                    idx = k;
                }
            }
            v[idx]=1;
            if (idx != -1)
            for (int k=0;k<m->numNodes;k++)
            {   
                if (d[k] > d[idx] + m->mat[idx][k] && m->mat[idx][k]!=0)
                    d[k] = d[idx] + m->mat[idx][k];
                
            }
        
    }

    for (int j=0;j<m->numNodes;j++)
    {
        printf("%d %d -> %d\n", nod,j,d[j]);
    }

    free(d);
    free(v);
}

int main()
{
    int n,e;

    scanf("%d%d",&n,&e);

    graphAdjMat_t * m = initGraph(n);
    graphEdge_t * vert = malloc (e * sizeof(graphEdge_t));

    int i,k=0;
    for (i=0;i<e;i++)
    {
        int u,v,w;

        scanf ("%d%d%d",&u,&v,&w);

        insertEdge(m,u,v,w);
        vert[k].u = u;
        vert[k].v = v;
        vert[k].cost = w;

        k++;
    }

    //topologial_sort(m);

    //Floyd_Warshall(m,vert,e);

    //Bellman_Ford(m,vert,e);

    /*for (int i=0;i<m->numNodes;i++)
        {
            dijkstra(m,vert,e,i);
        }*/

    free(vert);
    freeGraph(&m);
}