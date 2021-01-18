#include<stdio.h>
#include<stdlib.h>

struct AdjListNode {
    int val;
    struct AdjListNode *next;
};
struct AdjList {
    int v;
    struct AdjListNode **array;
};
struct AdjListNode* Newnode(int val){
    struct AdjListNode *newnode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}
void addEdge(int src, int dest, struct AdjList *List, int **matrix){
    matrix[src][dest] = matrix[dest][src]= 1;
    struct AdjListNode* newnode = Newnode(dest);
    newnode->next = List->array[src];
    List->array[src] = newnode;
    newnode = Newnode(src);
    newnode->next = List->array[dest];
    List->array[dest] = newnode;
}
void PrintAdjList(struct AdjList *List){
    printf("AdjList:\n");
    for(int i=0; i<List->v; i++){
        struct AdjListNode *temp = List->array[i];
        printf("%d--", i);
        while(temp != NULL){
            printf("->%d", temp->val);
            temp = temp->next;
        }
        printf("\n");
    }
}
void PrintAdjMatrix(int **matrix, int v){
    printf("Adj Matrix:\n");
    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
            printf("%d  ", matrix[i][j]);
        printf("\n");
    }
}
int maxDegreeList(struct AdjList *List){
    int maxDegree = 0;
    for(int i=0;i<List->v;i++){
        int temp = 0;
        struct AdjListNode *head = List->array[i];
        while(head != NULL){
            temp++;
            head = head->next;
        }
        if(temp > maxDegree)
            maxDegree = temp;
    }
    return maxDegree;
}
int maxDegreeMatrix(int** matrix, int v){
    int maxDegree = 0;
    for(int i=0; i<v; i++)
    {
        int temp = 0;
        for(int j=0;j<v;j++)
            if(matrix[i][j] == 1)
                temp++;
        if(temp >maxDegree)
            maxDegree = temp;
    }
    return maxDegree;
}
int emptyList(struct AdjList *List){
    for(int i=0; i<List->v;i++)
        if(List->array[i] != NULL)
            return 0;
    return 1;
}
int emptyMatrix(int **matrix, int v){
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            if(matrix[i][j]==1)
                return 0;
    return 1;
}
int checkEdgeList(struct AdjList *List, int src, int dest){
    struct AdjListNode *head = List->array[src];
    while(head != NULL){
        if(head->val == dest)
            return 1;
        head = head->next;
    }
    return 0;
}
int checkEdgeMatrix(int **matrix, int src, int dest){
    return matrix[src][dest];
}
int triangleList(struct AdjList *List){
    for(int a=0; a<List->v; a++){
        struct AdjListNode* b = List->array[a];
        while(b->next != NULL){
            if(checkEdgeList(List, b->val, a)){
                struct AdjListNode *c = b->next;
                while(c != NULL){
                    if( checkEdgeList(List, c->val, a) && checkEdgeList(List, b->val, c->val) && checkEdgeList(List, c->val, b->val))
                        return 1;
                    c = c->next;
                }
            }
            b = b->next;
        }
    }
    return 0;
}
int triangleMatrix(int **matrix, int v){
    for(int i=0; i<v; i++)
        for(int j=1; j<v-1; j++)
            if( matrix[j][i] )
                for(int k = j+1; k<v; k++)
                    if(matrix[k][i] && matrix[j][k] && matrix[k][j])
                        return 1;
    return 0;
}
int addEdgeList(struct AdjList *List, int src, int dest){
    if(List->v < src || List->v < dest)
        return 0;
    struct AdjListNode *newnode = Newnode(dest);
    newnode->next = List->array[src];
    List->array[src] = newnode;
    return 1;
}
int addEdgeMatric(int **matrix, int v, int src, int dest){
    if(v < src || v < dest)
        return 0;
    matrix[src][dest] = 1;
    return 1;
}
int deleteEdgeList(struct AdjList *List, int src, int dest){
    struct AdjListNode **head = &(List->array[src]);
    while((*head) != NULL){
        if((*head)->val == dest){
            *head = (*head)->next;
            return 1;
        }
        head = &((*head)->next);
    }
    return 0;
}
void deleteEdgematrix(int **matrix, int src, int dest){
    matrix[src][dest] = 0;
}
void subDivideEdgeList(struct AdjList *List, int src, int dest, int w){
    List->v++;
    List->array = (struct AdjListNode**)realloc(List->array, List->v*sizeof(struct AdjListNode*));
    struct AdjListNode *head = List->array[src];
    while(head != NULL){
        if(head->val == dest){
            head->val = w;
            break;
        }
        head = head->next;
    }
    List->array[List->v - 1] = Newnode(dest);
}
int** subDivideEdgeMatrix(int **matrix, int v, int src, int dest, int w){
    int **matrix2 = (int**)malloc((v+1)*sizeof(int*));
    for(int i=0;i<v+1;i++)
        matrix2[i] = (int*)calloc(v+1,sizeof(int));
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            matrix2[i][j] = matrix[i][j];
    matrix2[src][dest] = 0;
    matrix2[src][w] = 1;
    matrix2[w][dest] = 1;
    return matrix2;
}
int** complementGraph(int **matrix, int v){
    int **matrix2 = (int**)malloc(v*sizeof(int*));
    for(int i=0;i<v;i++)
        matrix2[i] = (int*)calloc(v,sizeof(int));
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            matrix2[i][j] = matrix[i][j];
}
int main(){
    struct AdjList *List = (struct AdjList*)malloc(sizeof(struct AdjList));
    List->v = 5;
    List->array = (struct AdjListNode **)malloc(List->v*sizeof(struct AdjListNode*));
    for(int i=0;i<5;i++)
        List->array[i] = NULL;
    int **matrix = (int**)malloc(5*sizeof(int*));
    for(int i=0;i<5;i++)
        matrix[i] = (int*)calloc(5,sizeof(int));
    addEdge(0,1,List, matrix);
    addEdge(0,4,List, matrix);
    addEdge(2,1,List, matrix);
    addEdge(2,3,List, matrix);
    addEdge(3,1,List, matrix);
    addEdge(3,4,List, matrix);
    addEdge(4,1,List, matrix);
    PrintAdjList(List);
    PrintAdjMatrix(matrix, List->v);
    printf("maxdegree %d %d \n", maxDegreeList(List), maxDegreeMatrix(matrix, 5));
    printf("empty: %d %d \n", emptyList(List), emptyMatrix(matrix, 5));
    printf("checkEdge %d %d \n", checkEdgeList(List, 0, 1), checkEdgeMatrix(matrix, 0, 1));
    printf("checkEdge %d %d \n", checkEdgeList(List, 0, 3), checkEdgeMatrix(matrix, 0, 3));
    addEdgeList(List, 0, 3);
    addEdgeMatric(matrix, 5, 0, 3);
    PrintAdjList(List);
    PrintAdjMatrix(matrix, List->v);
    deleteEdgeList(List, 0, 3);
    deleteEdgematrix(matrix, 0, 3);
    PrintAdjList(List);
    PrintAdjMatrix(matrix, List->v);
    subDivideEdgeList(List, 0, 1, 5);
    matrix = subDivideEdgeMatrix(matrix, 5, 0, 1, 5);
    PrintAdjList(List);
    PrintAdjMatrix(matrix, List->v);
}
// d, h, i