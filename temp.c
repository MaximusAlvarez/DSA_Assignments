#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

//Struct to hold  a node in MST
struct MstNode {
    int weight, parent;
    bool present;
};
typedef struct MstNode* MstNodeP;
//Struct to hold an MstArray
struct MstArray {
    int V;
    MstNodeP array;
};
typedef struct MstArray* MstArrayP;

//Func to return min element considering Mst Array as a priority queue with weight as key
int MinElement(MstArrayP MST){
    int min_element, min_weight = INT_MAX;
    for(int i=0; i<MST->V; i++)
        if(MST->array[i].present == false && MST->array[i].weight < min_weight){
            min_weight = MST->array[i].weight;
            min_element = i;
        }
    return min_element;
}

MstArrayP PrimMST(int* G, int V){
    //Intialization on MST array
    MstArrayP MST = (MstArrayP)malloc(sizeof(struct MstArray));
    MST->V = V;
    MST->array = (MstNodeP)malloc((MST->V)*sizeof(struct MstNode));
    for(int i=0; i<MST->V; i++){
        MST->array[i].weight = INT_MAX;
        MST->array[i].present = false;
        MST->array[i].parent = -1;
    }

    MST->array[0].parent = -1;
    MST->array[0].weight = 0;

    for(int i=0; i<MST->V; i++){
        int u = MinElement(MST);
        MST->array[u].present = true;
        
        for(int j=0; j<V; j++) {
            if(G[u*V + j] == 0)
                continue;
            if(MST->array[j].present == false && G[u*V + j] < MST->array[j].weight) {
                MST->array[j].parent = u;
                MST->array[j].weight = G[u*V + j];
            }
        }
    }

    return MST;
}
int* createGraph(int V) {
    int* G = (int*)malloc(sizeof(int)*V*V);

    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++) {
            int a;
            scanf("%d", &a);
            G[i*V + j] = a;
        }
    }
    return G;
}

int* printGraph(MstArrayP MST, int *m) {
    int min_cost = 0;
    int V = MST->V;
    int* G = (int*)calloc(V*V, sizeof(int));

    for(int i=0; i<MST->V; i++) {
        min_cost += MST->array[i].weight;
        G[MST->array[i].parent*V + i] = 1;
        G[MST->array[i].parent + i*V] = 1;
    }
    printf("%d\n", min_cost);

    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            printf("%d ", G[i*V + j]);
        }
        printf("\n");
    }

    *m = min_cost;
    return G;
}

void printModified(int *G, int min_cost, int V) {
    printf("%d\n", min_cost);

    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            printf("%d ", G[i*V + j]);
        }
        printf("\n");
    }
}

int changeEdge(int* G, int* output, int min, int u, int v, int w, int V) {
    int oldWeight = G[u*V + v];
    G[u*V + v] = w;
    G[u + v*V] = w;

    if(output[u*V + v] == 1) {
        min -= oldWeight;
        output[u*V + v] = 0;
        output[u + v*V] = 0;

        int count = 0, vertexWithoutParent;
        for(int i=0; i<V; i++)
            count += output[u*V + i];
        if(count)
            vertexWithoutParent = u;
        else
            vertexWithoutParent = v;
        
        int minWeight = INT_MAX, parent = 0;
        for(int i=0; i<V; i++) {
            if(G[vertexWithoutParent*V + i] != 0 && minWeight > G[vertexWithoutParent*V + i]) {
                minWeight = G[vertexWithoutParent*V + i];
                parent = i;
            }
        }
        min += minWeight;
        output[vertexWithoutParent*V + parent] = 1;
        output[vertexWithoutParent + parent*V] = 1;
    }
    return min;
}

int main() {
    char c = ' ';
    int V, u, v, w, min_cost;
    int *G, *output;
    MstArrayP MST;
    while(c != 's') {
        scanf("%c", &c);
        switch(c) {
            case 'm':
                scanf("%d", &V);
                G = createGraph(V);
                MST = PrimMST(G, V);
                output = printGraph(MST, &min_cost);
                break;
            case 'e':
                scanf("%d %d %d", &u, &v, &w);
                min_cost = changeEdge(G, output, min_cost, u-1, v-1, w, V);
                printModified(output, min_cost, V);
                break;
        }
    } 
    return 0;
}