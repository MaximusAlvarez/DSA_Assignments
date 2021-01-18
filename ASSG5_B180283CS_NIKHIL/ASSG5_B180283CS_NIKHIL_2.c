#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<stdlib.h>

//Struct to hold an edge
struct Edge {
    int src, dest, weight;
};
typedef struct Edge* EdgeP;
//Struct to hold an array of edges
struct EdgeArray {
    int E;
    EdgeP array;
};
typedef struct EdgeArray* EdgeArrayP;
//Struct to hold a vertex
struct Vertex {
    int val, parent, shortest_path_estimate;
};
typedef struct Vertex* VertexP;
//Struct to hold a vertex array which contains shortest path from a single-source
struct ShortestPathTree {
    int V;
    VertexP vertex_array;
};
typedef struct ShortestPathTree* ShortestPathTreeP;

EdgeArrayP CreateEdges(){
    EdgeArrayP E = (EdgeArrayP)malloc(sizeof(struct EdgeArray));
    scanf("%d", &(E->E) );
    E->array = (EdgeP)malloc( (E->E)*sizeof(struct Edge) );
    int src, dest, weight;
    for(int i=0; i< E->E; i++){
        scanf("%d %d %d", &src, &dest, &weight);
        E->array[i].src = src;
        E->array[i].dest = dest;
        E->array[i].weight = weight;
    }
    return E;
}

ShortestPathTreeP IntializeSPT(){
    ShortestPathTreeP G = (ShortestPathTreeP)malloc(sizeof(struct ShortestPathTree));
    scanf("%d", &(G->V) );
    G->vertex_array = (VertexP)malloc( (G->V)*sizeof(struct Vertex) );
    for(int i=0; i<(G->V); i++){
        G->vertex_array[i].val = i;
        G->vertex_array[i].parent = -1;
        G->vertex_array[i].shortest_path_estimate = INT_MAX;
    }
    return G;
}

void Relax(VertexP src, VertexP dest, int weight){
    if( dest->shortest_path_estimate > (long int)src->shortest_path_estimate + weight ){
        dest->parent = src->val;
        dest->shortest_path_estimate = src->shortest_path_estimate + weight; 
    }
}

bool Bellman_Ford(ShortestPathTreeP G, EdgeArrayP E, int S){
    G->vertex_array[S].shortest_path_estimate = 0;
    //Forms the Shortest path tree
    for(int i=1; i<G->V; i++)
        for(int j=0; j<E->E; j++){
            VertexP src, dest;
            src = G->vertex_array + E->array[j].src;
            dest = G->vertex_array + E->array[j].dest;
            Relax(src, dest, E->array[j].weight);
        }
    //Check for Negative Weigth Cycle
    for(int j=0; j<E->E; j++){
        VertexP src, dest;
        src = G->vertex_array + E->array[j].src;
        dest = G->vertex_array + E->array[j].dest;
        if( dest->shortest_path_estimate > (long int)src->shortest_path_estimate + E->array[j].weight )
            return false;
    }
    return true;
}

int main(){
    ShortestPathTreeP G = IntializeSPT();
    EdgeArrayP E = CreateEdges();
    int S;
    scanf("%d", &S);
    Bellman_Ford(G, E, S);
    for(int i=0; i<G->V; i++)
        printf("%d %d\n", i, G->vertex_array[i].shortest_path_estimate);
    return 0;
}