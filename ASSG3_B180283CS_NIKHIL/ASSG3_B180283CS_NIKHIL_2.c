#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
    int data;
    struct node *left,*right;
};
typedef struct node* AVLp;
void create(AVLp *tree){
    scanf(" (");
    int element;
    if(scanf("%d",&element)){
        AVLp newnode = (AVLp)malloc(sizeof(struct node));
        newnode->data = element;
        newnode->left = NULL;
        newnode->right = NULL;
        *tree = newnode;
        create(&((*tree)->left));
        create(&((*tree)->right));
    }
    scanf(" )");
}
int max(int a , int b){
    return (a>b)?a:b;
}
int isAVL(AVLp tree, AVLp l, AVLp r, int *height){
    if(tree == NULL)
        return 1;
    if(l!=NULL && l->data >= tree->data)
        return 0;
    if(r!= NULL && r->data < tree->data)
        return 0;
    int left=0, right=0, checkl, checkr;
    checkl = isAVL(tree->left, l, tree, &left);
    checkr = isAVL(tree->right, tree, r, &right);
    *height = max(left, right) + 1;
    if((left - right) < -1 || (left - right) > 1)
        return 0;
    return checkl && checkr;
}
int main(){
    AVLp tree;
    int h=0;
    tree=NULL;
    create(&tree);
    printf("%d", isAVL(tree, NULL, NULL, &h));
    // printf("%d", h);
    return 0;
}