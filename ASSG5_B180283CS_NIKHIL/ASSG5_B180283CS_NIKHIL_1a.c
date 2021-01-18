#include<stdio.h>
#include<stdlib.h>

//Struct to hold an edge
struct Edge {
    int src, dest, weight;
    struct Edge *next;
};
typedef struct Edge *EdgeP;

//Struct to hold an array of edges
struct EdgeArray {
    int V, E;
    EdgeP head;
};
typedef struct EdgeArray *EdgeArrayP;

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

//Struct for disjoint set node 
struct DisjointSetNode{
    int rank, val;
    struct DisjointSetNode *parent;
};
typedef struct DisjointSetNode* DisjointSetNodeP;
//Struct to hold DisjointSet
struct DisjointSet{
    int V;
    DisjointSetNodeP *set;
};
typedef struct DisjointSet* DisjointSetP;

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

    for(int i=0; i<V; i++)
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
void appendEdge(EdgeArrayP E, int src, int dest, int weight){
    EdgeP newEdge = (EdgeP)malloc(sizeof(struct Edge));
    newEdge->src = src;
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;

    if(E->head == NULL)
        E->head = newEdge;
    else {
        EdgeP *temp = &(E->head);
        while(*temp != NULL && (*temp)->weight < newEdge->weight)
            temp = &((*temp)->next);
        newEdge->next = *temp;
        *temp = newEdge;
    }
    E->E++;
}

EdgeArrayP MakeArrayEdges(GraphP G){
    EdgeArrayP E = (EdgeArrayP)malloc(sizeof(struct EdgeArray));
    E->V = G->V;
    E->E = 0;
    E->head = NULL;

    for(int i=0; i<G->V; i++){
        AdjacencyListNodeP adj_list = G->array[i].head;
        while(adj_list!=NULL){
            if(adj_list->vertex_key > i)
                appendEdge(E, i, adj_list->vertex_key, adj_list->weight);
            adj_list = adj_list->next;
        }
    }
    return E;
}

//Disjoint Set datastructure functions with ranked union and path compression
DisjointSetNodeP MakeSet(int x){
    DisjointSetNodeP newnode = (DisjointSetNodeP)malloc(sizeof(struct DisjointSetNode));
    newnode->val = x;
    newnode->parent = newnode;
    newnode->rank = 0;
    return newnode;
}

DisjointSetNodeP FindSet(DisjointSetNodeP x){
    if(x->parent != x) 
        x->parent = FindSet(x->parent);
    return x->parent;
}

void Union(DisjointSetNodeP x, DisjointSetNodeP y){
    DisjointSetNodeP xParent = FindSet(x), yParent = FindSet(y);
    // printf("%d %d\n", xParent->val, yParent->val);
    if(xParent->rank > yParent->rank)
        yParent->parent = xParent;
    else {
        xParent->parent = yParent;
        if(xParent->rank == yParent->rank)
            yParent->rank++;
    }
}

EdgeArrayP KruskalMST(EdgeArrayP E){
    DisjointSetP S = (DisjointSetP)malloc(sizeof(struct DisjointSet));
    EdgeArrayP MST = (EdgeArrayP)malloc(sizeof(struct EdgeArray));

    //Initializing Disjoint set
    S->V = E->V;
    S->set = (DisjointSetNodeP *)malloc((S->V)*sizeof(DisjointSetNodeP));
    for(int i=0; i<(S->V); i++)
        S->set[i] = MakeSet(i);

    // //Initializing MST
    MST->E = 0;
    MST->V = E->V;
    MST->head = NULL;

    EdgeP head = E->head;
    while(head != NULL){
        if(FindSet(S->set[head->src]) != FindSet(S->set[head->dest])){
            appendEdge(MST, head->src, head->dest, head->weight);
            Union(S->set[head->src], S->set[head->dest]);
        }
        head = head->next;
    }
    return MST;
}
int main() {
    GraphP G = CreateGraph();
    EdgeArrayP E = MakeArrayEdges(G);
    EdgeArrayP MST = KruskalMST(E);
    int min_cost = 0;
    EdgeP test = MST->head;
    while(test != NULL){
        min_cost += test->weight;
        test = test->next;
    }
    printf("%d", min_cost);
    return 0;
}