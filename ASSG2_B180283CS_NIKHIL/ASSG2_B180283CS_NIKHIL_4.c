#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
    int data;
    struct node *left,*right;
};
typedef struct node* BSTp;
void insert(BSTp *tree,int element){
    if(*tree == NULL){
        BSTp newnode = (BSTp)malloc(sizeof(struct node));
        newnode->data = element;
        newnode->left = NULL;
        newnode->right = NULL;
        *tree = newnode;
    }
    else if((*tree)->data<=element)
        insert(&((*tree)->right),element);
    else
        insert(&((*tree)->left),element);
    return;
}
void inorder(BSTp tree){
    if(tree == NULL)
        return;
    inorder(tree->left);
    printf("%d ",tree->data);
    inorder(tree->right);
    return;
}
void preorder(BSTp tree){
    if(tree == NULL)
        return;
    printf("%d ",tree->data);
    preorder(tree->left);
    preorder(tree->right);
    return;
}
void postorder(BSTp tree){
    if(tree == NULL)
        return;
    postorder(tree->left);
    postorder(tree->right);
    printf("%d ",tree->data);
    return;
}
void paren(BSTp tree){
    if(tree == NULL){
        printf("( ) ");
        return;
    }
    printf("( %d ",tree->data);
    paren(tree->left);
    paren(tree->right);
    printf(") ");
    return ;
}
int main(){
    BSTp tree;
    tree=NULL;
    int element,n;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&element);
        insert(&tree,element);
    }
    paren(tree);
    return 0;
}