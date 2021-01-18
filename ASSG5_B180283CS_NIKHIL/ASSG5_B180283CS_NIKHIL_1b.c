#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

//Struct to hold a node in a adjacency list
struct AdjacencyListNode {
    int vertex_key;
    int weight;
    struct AdjacencyListNode *next;
};
typedef struct AdjacencyListNode *AdjacencyListNodeP;

//Struct to hold an adjacency list
struct AdjacencyList {
    AdjacencyListNodeP head;
};
typedef struct AdjacencyList *AdjacencyListP;

//Struct to hold all the adjacency lists
struct Graph {
    int V;
    struct AdjacencyList *array;
};
typedef struct Graph *GraphP;

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

//Func to create a new Adjacency list node
AdjacencyListNodeP NewAdjListNode(int dest){
    AdjacencyListNodeP newnode = (AdjacencyListNodeP)malloc(sizeof(struct AdjacencyListNode));
    newnode->next = NULL;
    newnode->vertex_key = dest;
    newnode->weight = 0;
    return newnode;
}

//Func to append in linked list
AdjacencyListNodeP append(AdjacencyListNodeP head, AdjacencyListNodeP newnode){
    if(head == NULL)
        return newnode;
    AdjacencyListNodeP tail = head;
    while(tail->next != NULL)
        tail = tail->next;
    tail->next = newnode;
    return head;
}

//Intializes a graph of size V
GraphP CreateGraph(){
    int V;
    scanf("%d", &V);

    GraphP G = (GraphP)malloc(sizeof(struct Graph));
    G->V = V;
    G->array = (AdjacencyListP)malloc(V*sizeof(struct AdjacencyList));
    for(int i; i<V; i++)
        G->array[i].head = NULL;

    for(int i=0; i<V; i++){
        char temp = ' ';
        while(temp != '\n'){
            int vertex;
            scanf(" %d%c", &vertex, &temp);
            AdjacencyListNodeP newnode = NewAdjListNode(vertex);
            G->array[i].head = append(G->array[i].head, newnode);
        }
    }

    int weight;
    for(int i=0; i<V; i++){
        AdjacencyListNodeP adj_list = G->array[i].head;
        int weight;
        while(adj_list != NULL){
            scanf(" %d", &weight);
            adj_list->weight = weight;
            adj_list = adj_list->next;
        }
    }

    return G;
}

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

MstArrayP PrimMST(GraphP G){
    //Intialization on MST array
    MstArrayP MST = (MstArrayP)malloc(sizeof(struct MstArray));
    MST->V = G->V;
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
        
        AdjacencyListNodeP head = G->array[u].head;
        while(head != NULL){
            if(MST->array[head->vertex_key].present == false && head->weight < MST->array[head->vertex_key].weight){
                MST->array[head->vertex_key].parent = u;
                MST->array[head->vertex_key].weight = head->weight;
            }
            head = head->next;
        }
    }

    return MST;
}
int main() {
    GraphP G = CreateGraph();
    MstArrayP MST = PrimMST(G);
    int min_cost = 0;
    for(int i=0; i<MST->V; i++)
        min_cost += MST->array[i].weight;
    printf("%d", min_cost);
    return 0;
}