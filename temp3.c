#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int minKey(int key[], bool mstSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void primMST(int **graph, int V, int *key, int *parent)
{
    bool mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
}

void createGraph(int **G, int V)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int a;
            scanf("%d", &a);
            G[i][j] = a;
        }
    }
}

int main()
{
    int **graph;
    int V = 4;
    char c = ' ';
    int u, v, w, min_cost;
    int *G, **output, *key, *parent;
    while (c != 's')
    {
        scanf("%c", &c);
        switch (c)
        {
        case 'm':
            scanf("%d", &V);
            key = (int *)malloc(sizeof(int) * V);
            parent = (int *)malloc(sizeof(int) * V);
            graph = (int **)malloc(sizeof(int *) * V);
            for (int i = 0; i < V; i++)
                graph[i] = (int *)malloc(sizeof(int) * V);
            createGraph(graph, V);
            primMST(graph, V, key, parent);
            break;
        case 'e':
            scanf("%d %d %d", &u, &v, &w);
            u -= 1;
            v -= 1;
            G[u * V + v] = w;
            G[u + v * V] = w;
            break;
        }
    }

    output = (int **)malloc(sizeof(int*) * V);
    for (int i = 0; i < V; i++)
        output[i] = (int *)malloc(V*sizeof(int));
    int count = 0;
    for (int i = 0; i < V; i++)
    {
        count += key[i];
        int z = parent[i];
        output[i][z-1] = 1;
        output[z-1][i] = 1;
    }
    printf("%d", count);
    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            printf("%d ", output[i][j]);
        }
        printf("\n");
    }
    return 0;
}
